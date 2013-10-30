from sys import stdin, stdout

#fin = stdin
fin = open('input.txt')
fout = stdout
#fout = open('output.txt', 'w')

s = list(fin.read().strip().split())
n = list(map(len, s))

dp = [[0] * (n[1] + 1) for i in range(n[0] + 1)]
fr = [[(0, 0)] * (n[1] + 1) for i in range(n[0] + 1)]

for i in range(n[0]):
    for j in range(n[1]):
        dp[i][j], fr[i][j] = dp[i - 1][j], (i - 1, j)
        if dp[i][j] < dp[i][j - 1]:
            dp[i][j], fr[i][j] = dp[i][j - 1], (i, j - 1)
        if s[0][i] == s[1][j]:
        	dp[i][j], fr[i][j] = dp[i - 1][j - 1] + 1, (i - 1, j - 1)
            

ans = []
i, j = map(lambda x: x - 1, n)


while dp[i][j] != 0:
    if s[0][i] == s[1][j]:
        ans.append(s[0][i])
    i, j = fr[i][j]

print(''.join(ans[::-1]), file=fout)
