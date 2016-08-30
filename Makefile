pathName = "PATH=$$PATH:"
pathName := $(pathName)$(CURDIR)
myDir = /home/$(USER)/myShell
pathAddtion = /home/$(USER)/.bashrc



all: setPath makeDirectory
	gcc -o Shell main.c Utility.c Parser.c Constants.c SystemCalls.c
	

setPath:
	@echo $(pathName) >> $(pathAddtion)
	@echo $(pathName)

makeDirectory:
	mkdir -p $(myDir)
	touch $(myDir)/logFile.txt
	touch $(myDir)/history.txt
	

clean:
	rm -r $(myDir)
	rm Shell
	head -n -1 $(pathAddtion) > temp.txt 
	mv temp.txt $(pathAddtion) 
