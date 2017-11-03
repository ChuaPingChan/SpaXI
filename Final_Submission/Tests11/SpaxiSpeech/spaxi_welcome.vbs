Set spaxi=Createobject("sapi.spvoice")
Set spaxi.voice = spaxi.GetVoices.Item(2)
spaxi.rate = 3
if hour(time) < 12 then
spaxi.speak "Good morning, I am Spaxi."
else
if hour(time) > 12 then
if hour(time) > 16 then
spaxi.speak "Good evening, I am Spaxi."
else
spaxi.speak "Good afternoon, I am Spaxi."
end if
end if
end if
spaxi.speak "Welcome to Team 11's static analyzer program."