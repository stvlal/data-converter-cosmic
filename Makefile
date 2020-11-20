
CXX           = g++ -Wno-write-strings
ObjSuf        = o
SrcSuf        = cxx
ExeSuf        =
DllSuf        = so

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
ROOTINCLUDE  := -I$(shell root-config --incdir)



all:
	make Dictationarys
	make converter

converter: trb3.$(ObjSuf) trb3Dict.$(ObjSuf)
	$(CXX) -g -o $@ $^ $(ROOTGLIBS)



Dictationarys:
	rootcint -f trb3Dict.cxx -c -I`root-config --incdir` trb3.h
#	rootcint -f $(TARGETCINT) -c -I$(ROOTSYS)/include $(TARGET).h

%.$(ObjSuf): %.$(SrcSuf)
	$(CXX) -g -c $(ROOTINCLUDE) -c $<

clean:
	rm -f *.o
	rm -f *Dict*
	rm -f G__*
	rm converter
