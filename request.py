import sys, zmq

from_link = sys.argv[1]
to_link = sys.argv[2]

print "Sending query for path between '%s' and '%s'" % (from_link, to_link)

context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://127.0.0.1:37253")

socket.send("%s|%s" % (from_link, to_link))
response = socket.recv()

print "Received reply: %s", response
