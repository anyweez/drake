import MySQLdb, sys, re

## Function to strip all non-printable characters.
def asciify(text):
   return re.sub(r'[^\w]', '', text)

conn = MySQLdb.connect(user='root', passwd='lucAS101', db='wikimap')
cursor = conn.cursor()

# Delete all pre-existing articles and reset the autoincrement count.
cursor.execute("DELETE FROM articles")
cursor.execute("ALTER TABLE articles AUTO_INCREMENT = 1")
print 'Cleared article table...'

# Check that a filename was provided.
if len(sys.argv) is not 2:
   print 'Usage: python parsexml.py data-file.xml'
   print '   Note that the data file must be in the data/ subdir.  You do not '
   print '   need to specify this subdirectory in the argument.'
   sys.exit(1)
   
# Parse out all of the article names and give them unique ID's.
print '[1 / 2] Assigning unique IDs to each topic and updating database...'
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

   line = infile.readline()

infile.close()
conn.close()
