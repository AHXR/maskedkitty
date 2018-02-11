# maskedkitty

<p align="center">
	<img src="https://i.imgur.com/4bVahEg.gif" />
	<img src="https://i.imgur.com/6HHcNH6.png" />
</p>

---

**maskedkitty** is a light multi-purpose tool that allows you to modify an .exe file. This simple application allows you to do the following to an executable file:

- Inject/Change the icon
- Spoof the file extension
- Pump the file size to a higher size

The purpose of pumping a file size is to make a sent file seem more "legitimate". Optimized and compacted malware tends to be distributed at very small file sizes. This can make someone very suspicious of the file. The
file pumper allows you to increase the file size by KBs, MBs or GBs. As you can see from the .gif, it will tell you the estimated file size output. When using this feature, be wary of the build time. The more you pump into
a file, the longer the build time (depending on the user's hardware). Be patient. You can also refresh the directory where the target .exe is located to watch it increase in realtime.

The spoof extension is very simple. All this does is add your desired extension at the end of the *file name*, then it will add an .exe at the end of that. A common tactic is to use the icon changer to change the .exe to 
familiar extension's icon, then use this spoofer. For example, you can send an .exe file, spoof it as a .docx and use the Microsoft Word file icon to fool the target. They will think they are opening a Microsoft Word document
when in reality, they are running an .exe

This tool also includes an executable called "iconinjector". Unfortunately, C++ wasn't designed to directly work as a resource editor for executable files. With that being said, this executable was compiled from VB.NET.
The source code is included (credits to the original author).