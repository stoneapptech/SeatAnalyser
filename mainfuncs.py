from random import shuffle
def create():
	ltt=list(range(1,38))
	ltt.remove(4)
	shuffle(ltt)
	lt=[]
	for _ in range(6):
		r=[]
		for _ in range(6):
			r.append(ltt.pop())
		lt.append(r)
	return lt
def PrintArr(l):
	for i in l:
		for j in i:
			num=str(j)
			print((2-len(num))*'0'+num, end=' ')
		print()
def loadfile(filename):
	with open(filename) as f:
		r=[]
		for line in f.readlines():
			com=line.strip().split()
			r.append([int(com[0]), com[1], int(com[2])])
		return r
def find(l, num):
	for i_index, i in enumerate(l):
		for j_index, j in enumerate(i):
			if j==num:
				return i_index, j_index
