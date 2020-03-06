import sys
def editDistDP(str1, str2, m, n):
    dp = [[0 for x in range(n+1)] for x in range(m+1)]
 
    for i in range(m+1):
        for j in range(n+1):

            if i == 0:
                dp[i][j] = j 
 
            elif j == 0:
                dp[i][j] = i   
 
            elif str1[i-1] == str2[j-1]:
                dp[i][j] = dp[i-1][j-1]

            else:
                dp[i][j] = 1 + min(dp[i][j-1],        
                                   dp[i-1][j],       
                                   dp[i-1][j-1])   
    s1 = ""
    match = ""
    s2 = ""

    while(not (m==0 and n==0)):
          prev = dp[m][n]
          neighbour = []

          if (m!=0 and n!=0):
              neighbour.append(dp[m-1][n-1])
          if (m!=0):
              neighbour.append(dp[m-1][n])
          if (n!=0):
              neighbour.append(dp[m][n-1])
          min_cost = min(neighbour)

          if(min_cost == prev):
              m, n = m-1, n-1
              s1 += str1[m]
              match += "|"
              s2 += str2[n]
            
          elif(m!=0 and n!=0 and min_cost == dp[m-1][n-1]):
              m, n = m-1, n-1
              s1 += str1[m]
              match += " "
              s2 += str2[n]
              
          elif(m!=0 and min_cost == dp[m-1][n]):
              m = m-1
              s1 += str1[m]
              match += " "
              s2 += "-"
              
          elif(n!=0 and min_cost == dp[m][n-1]):
              n = n-1
              s1 += "-"
              match += " "
              s2 += str2[n]

    s1 = s1[::-1]
    match = match[::-1]
    s2 = s2[::-1]
    print()
    length = len(s1)
    if length >= 60:
        start, end = 0, 60
        while length >= 60:
            print(s1[start:end])
            print(match[start:end])
            print(s2[start:end])
            start += 60
            end += 60
            length -= 60
            print()
        print(s1[-length:])
        print(match[-length:])
        print(s2[-length:])
    else:
        print(s1)
        print(match)
        print(s2)

    print()
    return dp[-1][-1]


f1 = open(sys.argv[1],"r")
f2 = open(sys.argv[2],"r")
str1 = f1.read()
str2 = f2.read()
str1 = str1.replace("\n", " ")
str2 = str2.replace("\n", " ")

print ("optimal alignment: ")

print("edit distance =",editDistDP(str1, str2, len(str1), len(str2)))


