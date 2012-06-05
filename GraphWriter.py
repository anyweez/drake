import array

class GraphWriter(object):
	def __init__(self, filename):
		self.filename = filename
		self.fh = open(filename, 'wb')
		self.num_rows = 0
		self.max_id = 0
		self.outdata = array.array('I')
		
	def __del__(self):
		print 'Running destructor and writing graph to file.'
		
		newout = array.array('I')
		## Write all of the actual data.
		# Add the number of articles as the header data.
#		newout.append(int(str(self.num_rows), 10))
		newout.append(int(str(self.max_id), 10))
		newout.tofile(self.fh)
		
		self.outdata.tofile(self.fh)
		self.fh.close()
		print 'Write complete.'
		
	def write_row(self, node_id, neighbors):
		# Check to see if this is higher than the largest current ID we've seen.
		if node_id > self.max_id:
			self.max_id = node_id
			
		node_id = str(node_id)
		neighbors = [str(neigh) for neigh in neighbors]
		
		self.outdata.append(int(node_id, 10))
		self.outdata.append(int(str(len(neighbors)), 10))
		for neighbor in neighbors:
			self.outdata.append(int(neighbor, 10))
			
		self.num_rows += 1
