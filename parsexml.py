import xml.etree.cElementTree as ElementTree
import sys, re, array, MySQLdb

# Should eventually make this dynamic...
TOTAL_NUM_ARTICLES = 11600000

conn = MySQLdb.connect(user='root', passwd='lucAS101', db='wikimap')
cursor = conn.cursor()
link_pattern = re.compile("\[\[([a-zA-Z0-9_\(\)'|]*)\]\]")


#######################################################
### Function that takes an article body and returns ###
###    a list of links that appear inside of it.    ###
#######################################################
def get_links(body_text, pattern):
   if body_text is None:
	   return []

   # Find occurrences of [[]]
   # If contains |, take part before |.  If not, take whole thing.	   
   try:
      raw_links = re.findall(pattern, body_text)
   except:
	   print 'EXCEPTION!'
	   print body_text
	   print '[done]'
	   sys.exit(1)
	   
   for i, link in enumerate(raw_links):
      # This is wiki markup for [link|title]
      if '|' in link:
         raw_links[i] = link.split('|')[0]
      # This is wiki markup for [localization:link]
      elif ':' in link:
		  raw_links[i] = link.split(':')[1]
		  
   # Discard all duplicates...we're currently not using information about duplicate references.
   # Its possible that this could correlate with tie strength, but probably not a common signal.
   return list(set(raw_links))

#################################################################
### Removes all unprintable characters from the input string. ###
#################################################################
def asciify(text):
   return re.sub(r'[^\w]', '', text)

## This script parses the XML file named as the first argument.
## This file should be a Wikipedia dump that does not contain history.

# Check that a filename was provided.
if len(sys.argv) is not 2:
   print 'Usage: python parsexml.py data-file.xml'
   print '   Note that the data file must be in the data/ subdir.  You do not '
   print '   need to specify this subdirectory in the argument.'
   sys.exit(1)

print '[1 / 2] Loading articles from database...'

# SUBJECTS contains all article titles and maps to the article's unique ID.
subjects = {}
rowcount = 0

cursor.execute("SELECT article_id, title FROM articles")
result = cursor.fetchone()

while result is not None:
   subjects[result[1]] = int(result[0])
	
   if rowcount % 10000 is 0:
      sys.stdout.write('Completed %d rows.\r' % rowcount)

   rowcount += 1
   result = cursor.fetchone()
print ''
print '[1 / 2] Complete: loaded %d articles.' % len(subjects.keys())
print '[2 / 2] Parsing article edges...'

infile = open('%s' % sys.argv[1])

outdata = array.array('I')
# Add the number of articles as the header data.
outdata.append(int(str(len(subjects.keys())), 10))

# Parse the XML file one item at a time.  This isn't going to be paricularly fast
# but will keep us from running into memory constraints.
context = ElementTree.iterparse(infile, events=('start', 'end'))
context = iter(context)

event, root = context.next()

current_title = None
curr_node_list = []
#should_record = True
current_article_num = 0

for event, elem in context:
   # At the end of a title definition, extract the title and switch
   # the necessary state to declare that we're working on a new item.
   if event == 'end' and elem.tag.endswith('}title'):
      # Make sure this isn't the first iteration.  We won't have any
      # data to parse until after the first record has been fully
      # processed.
#      if current_title is not None:
#      if current_title is not None and should_record:

#      elif not should_record:
#         outdata.append(int('0', 10))
         
      # Empty the current node list.
      curr_node_list[:] = []
      current_title = asciify(elem.text)
      current_article_num += 1
      
      if current_article_num % 1000 is 0:
		  sys.stdout.write('Currently scanning [%d / %d]\r' % (current_article_num, TOTAL_NUM_ARTICLES))
		  sys.stdout.flush()

   # At the end of an article body, process the body and extract all
   # links.  If the link title isn't in the list of titles that we know
   # about, just skip and forget.
   if event == 'end' and elem.tag.endswith('}text'):
      links = get_links(elem.text, link_pattern)
      for link in links:
         try:
            curr_node_list.append(subjects[link])
         except KeyError:
            pass
      # Clear everything in the root so far once the record has been processed.
      root.clear()

      ### Convert all of the data to binary and store it in the OUTDATA
      ### vector.

      # Add the node ID to start off this record.
      try:  
         # This can potentially throw a KeyError exception if CURRENT_TITLE
         # refers to an article that we don't know about.
	     outdata.append(int(str(subjects[current_title]), 10))
#	     should_record = True

         # Add the number of edges that this node has.
         outdata.append(int(str(len(curr_node_list)), 10))
         # Add each of the nodes.
         for node in curr_node_list:
            outdata.append(int(str(node), 10))
      except KeyError:
         print 'unknown article: %s' % current_title
#	     should_record = False


# Record data for the last record.
outdata.append(int(str(len(curr_node_list)), 10))
for node in curr_node_list:
   outdata.append(int(str(node), 10))

outfile = open('wikimap.bin', 'wb')
outdata.tofile(outfile)
outfile.close()
infile.close()
print '[2 / 2] Complete.'
