JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	hsort.java \
	msort.java \
	qsortrandom1.java \
	qsortrandom2.java \
	qsort3median1.java \
	qsort3median2.java \
	qsort5median1.java \
	qsort5median2.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class