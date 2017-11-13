Set spaxi=Createobject("sapi.spvoice")
Set spaxi.voice = spaxi.GetVoices.Item(2)
spaxi.rate = 3

getCompliment(spaxi)

Sub getCompliment(spaxi)
	Dim bank(10)
	bank(0) = "You look great today."
	bank(1) = "On a scale from 1 to 10, you're an 11."
	bank(2) = "You should be thanked more often. So Thank you!"
	bank(3) = "There's ordinary, and then there's you"
	bank(4) = "You're really something special!"
	bank(5) = "You're a really strong person."
	bank(6) = "Your work on this project was incredible!"
	bank(7) = "You are an amazing friend."
	bank(8) = "I believe in you."
	bank(9) = "You look great when you smile. So give me a smile."
	
	randomize
	i = (rnd * 100) mod 10
	
	spaxi.speak bank(i)
End Sub
