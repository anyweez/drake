import MySQLdb, sys, re

## Function to strip all non-printable characters.
def asciify(text):
   return re.sub(r'[^\w]', '', text)

conn = MySQLdb.connect(user='root', passwd='lucAS101', db='drake')
cursor = conn.cursor()

# Delete all pre-existing articles and reset the autoincrement count.
print '[1 / 2] Clearing article table...'
cursor.execute("DELETE FROM articles")
cursor.execute("ALTER TABLE articles AUTO_INCREMENT = 1")
print 'Done.'

# Check that a filename was provided.
if len(sys.argv) is not 2:
   print 'Usage: python parsexml.py data-file.xml'
   print '   Note that this script expects to find a Wikipedia data dump '
   print '   (no edit history or talkback).'
   sys.exit(1)
   
# Parse out all of the article names and give them unique ID's.
print '[2 / 2] Assigning unique IDs to each topic and updating database...'
infile = open('%s' % sys.argv[1])

line = infile.readline()
subjects = {}
while len(line) > 0:
   # Look for title elements...this is easy enough that we don't need to parse the
   # file as XML.
   line = line.strip()
   if line.startswith('<title>') and line.endswith('</title>'):
      title = asciify(line[7:-8])
      cursor.execute('INSERT INTO articles (title) VALUES (%s);', title)
      subjects[title] = cursor.lastrowid
      
      if (cursor.lastrowid % 1000 == 0):
		  conn.commit()

   line = infile.readline()

conn.commit()

infile.close()
conn.close()
print 'Done.'
