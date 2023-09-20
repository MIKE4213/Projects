import pprint
import numpy as np

#paper = [
 #[0, 5, 0, 0, 0, 0, 0, 6, 0],
 #[0, 0, 0, 0, 0, 0, 0, 0, 1],
 #[2, 0, 0, 6, 0, 7, 0, 0, 3],
 #[9, 6, 0, 0, 4, 8, 0, 5, 2],
 #[4, 0, 0, 0, 0, 0, 0, 0, 0],
 #[0, 8, 0, 1, 0, 0, 0, 0, 0],
 #[5, 9, 0, 7, 0, 2, 0, 1, 6],
 #[0, 4, 0, 0, 0, 6, 0, 0, 0],
 #[0, 0, 8, 0, 0, 0, 0, 0, 0]
#]
paper = []

def userimput(paper):
 for i in range(1, 10):
    row = list(input("Row="))
    ints = []
    for n in row:
       ints.append(int(n))
    paper.append(ints)
    if i==9:
       print("Complete!")


def PPaper(P):
    for i in range(len(P)):
      if(i % 3 ==0):
         print("- - - - - - - - - - - - - -")
         
      for j in range(len(P[0])):
         if(j % 3 == 0):
            print(" | ", end="")
         if(j == 8):
            print(P[i][j])
         else:   
          print(str(P[i][j])+" ", end="")

PPaper(paper)


def check(P,x,y,num):
   for i in range(len(P[0])):
      if P[x][i] == num:
         return False
   for j in range(len(P)):
      if P[j][y] == num:
         return False
   
   xsquare = int(x/3)
   ysquare = int(y/3)
   
   for i in range(xsquare*3, xsquare*3+3):
       for j in range(ysquare*3, ysquare*3+3):
          if P[i][j] == num:
             return False
   return True


def pickempty(P):
    for i in range(len(P)):
       for j in range(len(P[0])):
          if P[i][j]==0:
             return i,j
    return False   
      
def solvesudoku(P):
   if pickempty(P) == False:
      return True
   else:
    x,y = pickempty(P)
    for i in range(1, 10):
       if check(P,x,y,i) == True:
         P[x][y]=i
         if solvesudoku(P)== True:
            return True
         else:
           P[x][y] = 0
    return False
   

solvesudoku(paper)
print("After solving the puzzle =====")
PPaper(paper)


