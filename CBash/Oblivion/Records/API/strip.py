import os, glob

for infile in glob.glob('*.cpp'):
    f = open(infile)
    contents = f.readlines()
    f.close()
    o = open(infile,'w')
    inEnum = False
    enumLines = []
    for l in contents[:-1]:
        l = l.rstrip() + '\n'
        if inEnum:
            enumLines += [l]
            if '}' in l:
                maxsize = max([line.find('=') for line in enumLines])
                for line in enumLines:
                    pos = line.find('=')
                    if pos != -1:
                        line = line[:pos] + ' ' * (maxsize - pos) + line[pos:]
                    o.write(line)
                inEnum = False
                enumLines = []
        else:
            o.write(l)
        if ' enum ' in l:
            inEnum = True
            
    l = contents[-1].rstrip()
    if inEnum:
        enumLines += [l]
        if '}' in l:
            maxsize = max([line.find('=') for line in enumLines])
            for line in enumLines:
                pos = line.find('=')
                if pos != -1:
                    line = line[:pos] + ' ' * (maxsize - pos) + line[pos:]
                o.write(line)
            inEnum = False
            enumLines = []
    else:
        o.write(l) 
    o.close()

for infile in glob.glob('*.h'):
    f = open(infile)
    contents = f.readlines()
    f.close()
    o = open(infile,'w')
    inEnum = False
    enumLines = []
    for l in contents[:-1]:
        l = l.rstrip() + '\n'
        if inEnum:
            enumLines += [l]
            if '}' in l:
                maxsize = max([line.find('=') for line in enumLines])
                for line in enumLines:
                    pos = line.find('=')
                    if pos != -1:
                        line = line[:pos] + ' ' * (maxsize - pos) + line[pos:]
                    o.write(line)
                inEnum = False
                enumLines = []
        else:
            o.write(l)
        if ' enum ' in l:
            inEnum = True
    l = contents[-1].rstrip()
    if inEnum:
        enumLines += [l]
        if '}' in l:
            maxsize = max([line.find('=') for line in enumLines])
            for line in enumLines:
                pos = line.find('=')
                if pos != -1:
                    line = line[:pos] + ' ' * (maxsize - pos) + line[pos:]
                o.write(line)
            inEnum = False
            enumLines = []
    else:
        o.write(l) 
    o.close()