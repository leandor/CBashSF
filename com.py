import subprocess
import _subprocess
x = r'C:\Program Files (x86)\Subversion\bin\svn.exe commit -F logmsg.txt'
startupinfo = subprocess.STARTUPINFO()
startupinfo.dwFlags |= _subprocess.STARTF_USESHOWWINDOW
exeArgs = ''
d = 1
while True:
    ins,err = subprocess.Popen(x, stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
    print ins
    print
    print err
    print
    if 'commit failed' in ins.lower() or 'commit failed' in err.lower():
        print "Try ", d, 'failed. Retrying...'
        print
        print
        d += 1
        continue
    else:
        print "Try ", d, ' SUCCESS!'
        break 