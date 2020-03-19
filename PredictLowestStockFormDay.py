stocks = [5,6,8,4,9,10,8,3,6,4]
stocks = [89214, 26671, 75144, 32445, 13656, 66289, 21951, 10265, 59857, 59133, 63227, 86121, 37411, 54628, 25859, 43510, 63756, 54763, 30852, 53243, 76238, 96885, 33074, 17745, 81814, 43436, 79172, 92819, 30001, 68442, 54021, 35566, 95113, 29164, 84362, 25120, 11804, 6313 , 51736, 71661, 81797, 14962, 57781, 35560, 85941, 99991, 95421, 66048, 54754, 26272, 35642, 47343, 39508, 85068, 65087, 21321, 28503, 60611, 30491, 58503, 29052, 84512, 94069, 40516, 13675, 78430, 65635, 25479, 1094 , 17370, 13491, 99243, 48683, 71271, 34802, 34624, 87613, 46574, 671, 42366, 89197, 36313, 89708, 28704, 21380, 54795, 66376, 49882, 15405, 96867, 24737, 60808, 81378, 35157, 1324, 11404, 29938, 66958, 53234, 47384 ]

query = [3,1,8]
query = [80, 24, 26, 62, 46, 79, 85, 59, 52, 8 , 76, 48, 72, 84, 3 , 3 , 30, 30, 36, 86, 96, 72, 93, 25, 28, 68, 81, 18, 78, 14, 1 , 57, 90, 26, 18, 87, 56, 55, 97, 59, 62, 73, 58, 85, 8 , 60, 87, 89, 89, 22]
stocks[query[7]]

#index = np.argmin(np.array(stocks)-stocks[3-1])
#sa = np.array(stocks )
#sa-stocks[query[0]-1]

def predictAnswer(stockData, queries):
  query_out=[]
  for q in queries:
    qv = stockData[q-1]
    minidx=-1
    minvals = []
    minqv=qv
    for i,sp in enumerate(stockData):
      if sp < qv:
        minvals.append( (abs(i+1-q), sp, i+1) )
        minqv=sp
        minidx=i
        """
        if sp <= minqv:
          minqv=sp
          minidx=i
          if len(minvals)>0:
            minvals.pop()
        """
        #minvals.append( (abs(i-(q-1)),sp, i) )
    minvals.sort( key=lambda element: (element[0], element[1]))
    if q==59:
      print(minvals)
    if len(minvals)==0:
      query_out.append(-1)
    if len(minvals)>=1:
      query_out.append(minvals[0][2])
  return(query_out)

predictAnswer(stockData=stocks, queries=query)
#def predictAnswer(stockData, queries):
    # Write your code here
stocks[61-1]
stocks[57-1]

stocks[59-1]
