import os, glob

for infile in glob.glob('*.cpp'):
    f = open(infile)
    contents = f.readlines()
    f.close()
    o = open(infile,'w')
    [o.write(l.rstrip() + '\n') for l in contents]
    o.close()

for infile in glob.glob('*.h'):
    f = open(infile)
    contents = f.readlines()
    f.close()
    o = open(infile,'w')
    [o.write(l.rstrip() + '\n') for l in contents]
    o.close()