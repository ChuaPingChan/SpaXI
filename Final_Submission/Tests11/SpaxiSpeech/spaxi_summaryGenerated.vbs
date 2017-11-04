Set spaxi=Createobject("sapi.spvoice")
Set spaxi.voice = spaxi.GetVoices.Item(2)
spaxi.rate = 3
spaxi.speak "Summary Generated."