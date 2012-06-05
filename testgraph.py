import GraphWriter

gwriter = GraphWriter.GraphWriter('wikimap.bin')

gwriter.write_row(0, [1, 2])
gwriter.write_row(1, [0,])
gwriter.write_row(2, [0, 5])
gwriter.write_row(3, [0, 1, 2])
gwriter.write_row(5, [2,10])
gwriter.write_row(8, [5, 3, 1])
gwriter.write_row(10, [8, 2, 3, 1])
