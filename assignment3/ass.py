import sys
print "script name:"
print sys.argv[0]
if len(sys.argv)<3:
	print "lenth of argv less than 3"
	quit()

def main():
	fileHandle = open('trace.txt')
	while True:
	        page_num = fileHandle.readline()
		print page_num
		if not page_num: break
	fileHandle.close()


main()
