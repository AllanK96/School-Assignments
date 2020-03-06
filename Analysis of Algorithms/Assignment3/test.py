import time
import sys

# Yes it's Python 3, I only read the "note" at the bottom of the assignment after I had finished the assignment.
# Hopefully it doesn't impact the result. But the fact that it wasn't even mentioned in Q7 is odd.

def bruteForce(pat, txt):
    start = time.time()
    count = 0
    M = len(pat)
    N = len(txt)
    for i in range(0,N-M):
        for j in range(M):
            if txt[i + j] != pat[j]:
                break
        if j == M-1:
            count+=1
    
    end = time.time()
    return (count)


def badCharHeuristic(string, size):
    badChar = [-1]*65535
    for i in range(size):
        badChar[ord(string[i])] = i;
    return badChar

def boyer(pat, txt):
    start = time.time()
    
    m = len(pat)-1
    n = len(txt)
    count = 0
    badChar = badCharHeuristic(pat, m) 
    
    s = 0
    while(s <= n-m):
        
        j = m-1
        
        while j>=0 and pat[j] == txt[s+j]:
            j-=1
            
        if j<0:
            count += 1
            s += (m-badChar[ord(txt[s+m])] if s+m<n else 1)
        else:
            s += max(1, j-badChar[ord(txt[s+j])])
            
    #print (count)
    end = time.time()
    return(end-start)


def binSAsearch(P, A, txt):
    start = time.time()
    n = len(A)
    l = 0; r = n-1

    while l < r:
        mid = (l+r)// 2
        
        if P > txt[A[mid]:]:
            l = mid + 1
        else:
            r = mid
        
    s = l; r = n-1
    l = 0
    while l < r:
        mid = (l+r) // 2     
        if P == txt[A[mid]:(A[mid]+len(P))]: 
            l = mid + 1
        elif P < txt[A[mid]:]:
            r = mid
        else:
            l = mid + 1
    end = time.time()
    #print(abs(r-s)) #This would be the number of occurrences
    return(end-start) 



f1 = open(sys.argv[1],"r")
f2 = open(sys.argv[2],"r")
f3 = open(sys.argv[3],"r")

txt = f1.read()
txt = txt.replace("\n"," ")


suffArr = []
for line in f2:
	suffArr.append(int(line))

pat = []
for line in f3:
    pat.append(line)

for i in pat:
	print ("text: \""+f1.name+"\"")
	print ("pattern: \""+i.strip('\n')+"\"")
	start = time.time()
	print ("occurrences:",bruteForce(i,txt))
	end = time.time()
	print ("Brute Force: ",(end-start))
	print ("Boyer-Moore: ",boyer(i,txt))
	print ("Suffix Array: ",binSAsearch(i,suffArr,txt))
	print()

#Something must be wrong with my txt file or the suffix array file because
#The function works normally when manually given any sufficient data.

#suffArr = [17,1,13,4,9,2,18,14,5,10,19,16,0,3,8,15,6,11,7,12]
#txt = "TESTESTXTESTYESTTEST"
#pat = "EST"
#print (binSAsearch(pat, suffArr, txt))

