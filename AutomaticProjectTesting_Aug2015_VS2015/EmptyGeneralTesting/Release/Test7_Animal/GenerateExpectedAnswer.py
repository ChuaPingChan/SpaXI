VARIABLES = ["alpaca","antelope","badger","bear","bird","camel","anaconda","cat","dog","deer","cow","elephant","dinosaur","dolphin","eagle","earthworm","eel","flea","fly","flamingo","gazelle","gorilla","hawk","hedgehog","human","hamster","iguana","jaguar"]

# Query 1 Expected Answer
query1Ans = ''
for i in range(1,184):
	for j in range (1, 184):
		query1Ans += str(i) + ' ' + str(j) + ','
query1Ans = query1Ans[:-1]
print("Expected Answer for Q1: ")
print(query1Ans)
print()

#Query 2 Expected Answer
query2Ans = ''
for i in range (1, 184):
	for var in VARIABLES:
		query2Ans += str(i) + ' ' + var + ','
query2Ans = query2Ans[:-1]
print("Expected Answer for Q2: ")
print(query2Ans)
