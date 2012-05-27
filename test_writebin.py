import array

outfile = open('wikimap.bin', 'wb')
nums = array.array('I')

# There are two nodes in the dataset.
nums.append(int('4', 10))
# Node 32 is connected to 11, 12, and 18.
nums.append(int('0', 10))
nums.append(int('2', 10))
nums.append(int('1', 10))
nums.append(int('2', 10))

# Node 18 is connected to 4.
nums.append(int('1', 10))
nums.append(int('2', 10))
nums.append(int('0', 10))
nums.append(int('2', 10))

nums.append(int('2', 10))
nums.append(int('2', 10))
nums.append(int('1', 10))
nums.append(int('3', 10))

nums.append(int('3', 10))
nums.append(int('2', 10))
nums.append(int('2', 10))

nums.tofile(outfile)
outfile.close()
