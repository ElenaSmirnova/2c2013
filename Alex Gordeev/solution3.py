from sys import stdin, stdout

fin = stdin
#fin = open('input.txt')
fout = stdout
#fout = open('output.txt', 'w')

n = int(fin.readline())

ans = [[] for  i in range(n)]

for i in range(n):
	for j in range(n):
		ans[(i + j) % n].append(i * n + j + 1)

for i in range(n):
	print(' '.join(map(str, ans[i])), ' , sum = ', sum(ans[i]))