import re
import sys
from collections import OrderedDict
import os, glob

caseStart = 29

for curFile in glob.glob('*.h'):
    if curFile in ('GenericChunks.h', 'Opt.h', 'replRecord.h'):
        continue
    re_var = re.compile(' (.*?)(,|;)')
    re_struct = re.compile('struct (.*?)( |//|$)')
    re_rectype = re.compile('\<(.*?)\>')
    f = open('GenericChunks.h')
    GenericChunks = f.readlines()
    f.close()

    f = open(curFile)
    contents = f.readlines()
    f.close()
    ISTRINGS = ('EDID','ICON', 'MICO', 'SCTX', 'SCVR', 'MODL')
    types = ['UINT8', 'UINT16', 'UINT32', 'FORMID',
             'SINT8', 'SINT16', 'SINT32',
             'FLOAT32',
             'MGEFCODE_OR_UINT32', 'FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32'
             'FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32',
             'ACTORVALUE', 'FORMID_OR_UINT32', 'RawRecord', 'NonNullStringRecord', 'StringRecord']
    recs = ['ReqSimpleSubRecord', 'SemiOptSimpleSubRecord', 'OptSimpleSubRecord', 
            'ReqSubRecord', 'SemiOptSubRecord', 'OptSubRecord', 'OBMEEFIXSubRecord',
            'SimpleFloatSubRecord', 'ReqSimpleFloatSubRecord', 'OptSimpleFloatSubRecord',
            'SemiOptSimpleFloatSubRecord',
            'UnorderedPackedArray', 'OrderedPackedArray',
            'UnorderedSparseArray', 'OrderedSparseArray',
            'SimpleSubRecord', 'SubRecord', 'std::vector']

    modelSig = [('MODL', 'StringRecord', 0, False, []), ('MODB', 'SimpleFloatSubRecord', 0, False, [('', 'FLOAT32', 0, False, [])]), ('MODT', 'RawRecord', 0, False, []), ('MODS', 'std::vector', 0, True, [('texture', 'FORMID', 0, False, []), ('index', 'SINT32', 0, False, [])]), ('MODD', 'OptSimpleSubRecord', 0, False, [('', 'UINT8', 0, False, [])])]
    str_vars = OrderedDict()
    str_funcs = OrderedDict()
    vars = []
    funcs = []
    inStruct = False
    inType = False
    _rec = None
    for line in GenericChunks:
        if '//' in line:
            line = line[:line.find('//')]
        if 'struct ' in line:
            try:
                tag = re_struct.search(line).group(1)
                qual = tag
            except:
                print line
                raise
            inStruct = True
            braceCount = 0
        elif inStruct:
            if '{' in line:
                braceCount += 1
            if '}' in line:
                braceCount -= 1
            if '};' in line and braceCount == 0:
                inStruct = False
                str_vars[qual] = (tag, vars)
                str_funcs[qual] = (tag, funcs)
                types.append(tag)
                vars = []
                funcs = []
            elif '(' in line:
                l = line[:line.find('(')]
                v = line[line.find('(') + 1:line.rfind(')')]
                funcs += [(qual, l[l.rfind(' '):].strip(), v)]
            elif inType:
                l = line.strip(' \n').split(',')
                v = []
                for a in l:
                    s = None
                    n = a.strip(' ;\n')
                    if '[' in n:
                        s = n[n.find('[') + 1:n.find(']')]
                        try:
                            s = int(s)
                        except ValueError:
                            try:
                                s = int(s, 16)
                            except:
                                raise
                        n = n[:n.find('[')]
                    if len(n) > 0:
                        v += [(n, type, s, '*' in type, [])]
                vars += v
                if ';' in line:
                    inType = False
                    _type = None
            else:
                _rec = None
                _type = None
                for rec in recs:
                    if rec in line:
                        v = []
                        
                        if 'Float' in rec:
                            _type = 'FLOAT32'
                            line = line[line.find('>') + len('>'):].strip()
                        else:
                            line = line[line.find('<') + len('<'):].strip()
                            _type = line[:line.rfind('>')].split(',')[0]
                            line = line[line.rfind('>') + 1:].strip()
                        n = line.strip(' ;\n')
                        v += [('', _type, 0, False, [])]
                        vars += [(n, rec, 0, '*' in _type, v)]
                        _rec = rec
                        break
                if _rec is None:
                    for type in types:
                        if type in line:
                            line = line[line.find(type) + len(type):]
                            l = line.split(',')
                            v = []
                            for a in l:
                                s = 0
                                n = a.strip(' ;\n')
                                if '[' in n:
                                    s = n[n.find('[') + 1:n.find(']')]
                                    try:
                                        s = int(s)
                                    except ValueError:
                                        try:
                                            s = int(s, 16)
                                        except:
                                            raise
                                    n = n[:n.find('[')]
                                if len(n) > 0:
                                    v += [(n, type, s, '*' in type, [])]
                            vars += v
                            if ';' not in line:
                                inType = True
                                _type = type
                            break

    cl_vars = []
    cl_funcs = []
    vars = []
    funcs = []
    inStruct = False
    inType = False
    inPublic = False
    _rec = None
    cltag = ''
    skipFuncs = ['VisitFormIDs',
                 'GetFieldAttribute',
                 'GetField',
                 'SetField',
                 'DeleteField',
                 'GetType',
                 'GetStrType',
                 'ParseRecord',
                 'Unload',
                 'WriteRecord',
                 '==',
                 '!=',
                 ]

    for line in contents:
        if '//' in line:
            line = line[:line.find('//')]
        if 'class ' in line:
            line = line[6:]
            cltag = line[:line.find(' ')]
        elif 'public:' in line:
            inPublic = True
        elif 'struct ' in line:
            try:
                tag = re_struct.search(line).group(1)
                qual = cltag + '::' + tag
            except:
                print line
                raise
            inStruct = True
            braceCount = 0
        elif inStruct:
            if '{' in line:
                braceCount += 1
            if '}' in line:
                braceCount -= 1
            if '};' in line and braceCount == 0:
                inStruct = False
                str_vars[qual] = (tag, vars)
                str_funcs[qual] = (tag, funcs)
                types.append(tag)
                vars = []
                funcs = []
            elif '(' in line:
                l = line[:line.find('(')]
                v = line[line.find('(') + 1:line.rfind(')')]
                funcs += [(qual, l[l.rfind(' '):].strip(), v)]
            elif inType:
                l = line.strip(' \n').split(',')
                v = []
                for a in l:
                    s = None
                    n = a.strip(' ;\n')
                    if '[' in n:
                        s = n[n.find('[') + 1:n.find(']')]
                        try:
                            s = int(s)
                        except ValueError:
                            try:
                                s = int(s, 16)
                            except:
                                raise
                        n = n[:n.find('[')]
                    if len(n) > 0:
                        v += [(n, type, s, '*' in type, [])]
                vars += v
                if ';' in line:
                    inType = False
                    _type = None
            else:
                _rec = None
                _type = None
                for rec in recs:
                    if rec in line:
                        v = []
                        if 'Float' in rec:
                            _type = 'FLOAT32'
                            line = line[line.find('>') + len('>'):].strip()
                        else:
                            line = line[line.find('<') + len('<'):].strip()
                            _type = line[:line.rfind('>')].split(',')[0]
                            line = line[line.rfind('>') + 1:].strip()
                        n = line.strip(' ;\n')
                        v += [('', _type, 0, False, [])]
                        vars += [(n, rec, 0, '*' in _type, v)]
                        _rec = rec
                        break
                if _rec is None:
                    for type in types:
                        if type in line:
                            line = line[line.find(type) + len(type):]
                            l = line.split(',')
                            v = []
                            for a in l:
                                s = 0
                                n = a.strip(' ;\n')
                                if '[' in n:
                                    s = n[n.find('[') + 1:n.find(']')]
                                    try:
                                        s = int(s)
                                    except ValueError:
                                        try:
                                            s = int(s, 16)
                                        except:
                                            raise
                                    n = n[:n.find('[')]
                                if len(n) > 0:
                                    v += [(n, type, s, '*' in type, [])]
                            vars += v
                            if ';' not in line:
                                inType = True
                                _type = type
                            break
        elif inPublic:
            if '};' in line:
                inPublic = False
                cl_vars = vars
                cl_funcs = funcs
                vars = []
                funcs = []
            elif '(' in line:
                l = line[:line.find('(')]
                v = line[line.find('(') + 1:line.rfind(')')]
                l = l[l.rfind(' '):].strip()
                if l not in skipFuncs and cltag not in l:
                    funcs += [(cltag, l, v)]
            else:
                _rec = None
                _type = None
                for rec in recs:
                    if rec in line:
                        v = []
                        if 'Float' in rec:
                            _type = 'FLOAT32'
                            line = line[line.find('>') + len('>'):].strip()
                        else:
                            line = line[line.find('<') + len('<'):].strip()
                            _type = line[:line.rfind('>')].split(',')[0]
                            line = line[line.rfind('>') + 1:].strip()
                        n = line.strip(' ;\n')
                        v += [('', _type, 0, False, [])]
                        vars += [(n, rec, 0, '*' in _type, v)]
                        _rec = rec
                        break
                if _rec is None:
                    for type in types:
                        if type in line:
                            line = line[line.find(type) + len(type):]
                            l = line.split(',')
                            v = []
                            for a in l:
                                s = 0
                                n = a.strip(' ;\n')
                                if '[' in n:
                                    s = n[n.find('[') + 1:n.find(']')]
                                    try:
                                        s = int(s)
                                    except ValueError:
                                        try:
                                            s = int(s, 16)
                                        except:
                                            raise
                                    n = n[:n.find('[')]
                                if len(n) > 0:
                                    v += [(n, type, s, '*' in type, [])]
                            vars += v
                            break
                
    madeChanges = True
    def expandTypes(vs):
        global madeChanges
        v = []
        for name, type, size, ip, vars in vs:
            if len(vars):
                vars = expandTypes(vars)
            t = type.strip(' *')
            if t in str_vars:
                madeChanges = True
                v += str_vars[t][1]
            elif cltag + '::' + t in str_vars:
                madeChanges = True
                v += str_vars[cltag + '::' + t][1]
            else:
                v += [(name, type, size, ip, vars)]
        return v

    while madeChanges:
        madeChanges = False
        for str, vars in str_vars.iteritems():
            v = expandTypes(vars[1])
            str_vars[str] = (vars[0], v)
     
    madeChanges = True
    while madeChanges:
        madeChanges = False
        cl_vars = expandTypes(cl_vars)

    topchunks = [v[0] for v in cl_vars]

    def makeFids(vs, history=[]):
        global madeChanges, indent
        attrs = []
        for name, type, size, ip, vars in vs:
            t = type.strip(' *')
            s = len(vars)
            if 'unused' in name.lower() and (size is None or size == 0):
                size = 1
            if s == 1 and vars[0][0] == '':
                s = 0
                t = vars[0][1]
            if s > 0:
                vk = makeFids(vars, history + [(name, type, ip)])
                if 'Array' in type and len(vk):
                    topname, toptype, topip = name, type, ip
                    caseNum = 1
                    x = []
                    pre = []
                    prel = []
                    if len(history):
                        for hn, ht, hp in history:
                            if 'SemiOpt' in ht:
                                prel += ['%s.IsLoaded()' % hn]
                                pre += ['%s->' % hn]
                            elif 'Opt' in ht:
                                prel += ['%s.IsLoaded()' % hn]
                                pre += ['%s->' % hn]
                    else:
                        pre += ['%s.' % topname]
                        if 'SemiOpt' in toptype:
                            prel += ['%s.IsLoaded()' % topname]
                        elif 'Opt' in toptype:
                            prel += ['%s.IsLoaded()' % topname]
                    loads = ' && '.join(prel)
                    pres = ''.join(pre)
##                    if prel:
##                        attrs.append('            %s\n' % (loads,))
                    x.append('    for(UINT32 ListIndex = 0; ListIndex < %svalue.size(); ListIndex++)\n' % (pres,))
                    if len(vk) > 1:
                        x.append('        {\n')

                    did = False
                    did2 = False
                    for attr in vk:
                        did = False
                        for pre in prel:
                            if pre in attr:
                                did = True
                                did2 = True
                                break
                        if did: continue
                        if did2:
                            if '{' in attr:
                                continue
                            if '}' in attr:
                                continue
                            if 'return' in attr:
                                did2 = False
                            else:
                                attr = attr[4:]

##                        if 'SCR_' in topname:
##                            x.append('    for(UINT32 x = 0; x < %sSCR_.value.size(); x++)\n' % (pres,))
##                            x.append('        if(%sSCR_.value[x]->isSCRO)\n' % (pre,))
##                            x.append('            op.Accept(%sSCR_.value[x]->reference);' % (pres,))
##                        else:
                        rf = attr.rfind(topname)
                        if rf > 0:
                            if topip:
                                attr = attr[:attr.rfind(topname) + len(topname)] + '.value[ListIndex]->' + attr[attr.rfind(topname) + len(topname) + 1:]
                            else:
                                attr = attr[:attr.rfind(topname) + len(topname)] + '.value[ListIndex].' + attr[attr.rfind(topname) + len(topname) + 1:]
                        if len(vk) > 1:
                            x.append('    ' + attr)
                    if len(vk) > 1:
                        x.append('        }\n')
                    attrs += x
                elif vk:
                    attrs += vk
            else:
                pre = []
                prel = []
                if len(history):
                    for hn, ht, hp in history:
                        if 'SemiOpt' in ht:
                            prel += ['%s.IsLoaded()' % hn]
                        elif 'Opt' in ht:
                            prel += ['%s.IsLoaded()' % hn]
                        if 'Simple' in ht:
                            pre += ['%s.' % hn]
                        else:
                            if 'Req' in ht:
                                pre += ['%s.value.' % hn]
                            elif 'SemiOpt' in ht:
                                pre += ['%s->' % hn]
                            elif 'Opt' in ht:
                                pre += ['%s->' % hn]
                            elif 'Array' in ht:
                                pre += ['%s.' % hn]
                            else:
                                pre += ['%s.value.' % hn]
                else:
                    if 'SemiOpt' in type:
                        prel += ['%s.IsLoaded()' % name]
                    elif 'Opt' in type:
                        prel += ['%s.IsLoaded()' % name]
                pres = ''.join(pre)
                loads = ' && '.join(prel)

                if 'StringRecord' in t:
                    continue
                elif t == 'RawRecord':
                    continue

                elif 'SCR_' in pres:
                    attrs.append('    if(%sSCR_.value[ListIndex]->isSCRO)\n' % (pres,))
                    attrs.append('        op.Accept(%sSCR_.value[ListIndex]->reference);\n' % (pres,))
                elif t == 'FORMID':
                    if size:
                        if loads:
                            attrs.append('    if(%s)\n' % (loads,))
                            if size > 1:
                                attrs.append('        {\n')
                                for z in range(size):
                                    attrs.append('        op.Accept(%s%s[%d]);\n' % (pres, name, z))
                                attrs.append('        }\n')
                            else:
                                attrs.append('        op.Accept(%s%s);\n' % (pres, name))
                        else:
                            if size > 1:
                                for z in range(size):
                                    attrs.append('    op.Accept(%s%s[%d]);\n' % (pres, name, z))
                            else:
                                attrs.append('    op.Accept(%s%s);\n' % (pres, name))
                    elif 'MODL->MODS.value.texture' == '%s%s' % (pres, name):
                        attrs.append('    if(MODL.IsLoaded())\n')
                        attrs.append('        {\n')
                        attrs.append('        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)\n')
                        attrs.append('            op.Accept(MODL->Textures.MODS[x]->texture);\n')
                        attrs.append('        }\n')
                    elif 'Array' in type:
                        if loads:
                            attrs.append('    if(%s)\n' % (loads,))
                            attrs.append('        {\n')
                            if ip:
                                attrs.append('        for(UINT32 ListIndex = 0; ListIndex < %s%s.value.size(); ListIndex++)\n' % (pres,name))
                                attrs.append('            op.Accept(%s%s.value[ListIndex]->%s%s);\n' % (pres,name, pres,name))
                            else:
                                attrs.append('        for(UINT32 ListIndex = 0; ListIndex < %s%s.value.size(); ListIndex++)\n' % (pres,name,))
                                attrs.append('            op.Accept(%s%s.value[ListIndex]);\n' % (pres,name,))
                            attrs.append('        }\n')
                        else:
                            if ip:
                                attrs.append('    for(UINT32 ListIndex = 0; ListIndex < %s%s.value.size(); ListIndex++)\n' % (pres,name))
                                attrs.append('        op.Accept(%s%s.value[ListIndex]->%s%s);\n' % (pres,name, pres,name))
                            else:
                                attrs.append('    for(UINT32 ListIndex = 0; ListIndex < %s%s.value.size(); ListIndex++)\n' % (pres,name,))
                                attrs.append('        op.Accept(%s%s.value[ListIndex]);\n' % (pres,name,))
                    else:
                        if loads:
                            attrs.append('    if(%s)\n' % (loads,))
                            if 'Simple' in type:
                                pres += '%s.' % name
                                if 'SemiOpt' in type:
                                    attrs.append('        op.Accept(*%svalue);\n' % (pres))
                                else:
                                    attrs.append('        op.Accept(%svalue);\n' % (pres))
                            else:
                                attrs.append('        op.Accept(%s%s);\n' % (pres, name))
                        else:
                            if 'Simple' in type:
                                pres += '%s.' % name
                                if 'SemiOpt' in type:
                                    attrs.append('    op.Accept(*%svalue);\n' % (pres))
                                else:
                                    attrs.append('    op.Accept(%svalue);\n' % (pres))
                            else:
                                attrs.append('    op.Accept(%s%s);\n' % (pres, name))
        return attrs

    indent = 1
    if False:
        pass
        ##    def makeFids(vs, history=[]):
        ##        global madeChanges, indent
        ##        v = []
        ##        for name, type, size, ip, vars in vs:
        ##            t = type.strip(' *')
        ##            s = len(vars)
        ##            if s > 0:
        ##                if s == 1 and vars[0][0] == '':
        ##                    vk = makeFids([(name, vars[0][1], size, ip, [])], history + [(name, type, ip)])
        ##                    print vk
        ##                    print [(name, vars, size, ip, [])], history + [(name, type, ip)]
        ##                else:
        ##                    indent += 1
        ##                    vk = makeFids(vars, history + [(name, type, ip)])
        ##                    indent -= 1
        ##                if vk:
        ##                    pre = []
        ##                    prel = []
        ##                    if len(history):
        ##                        for hn, ht, hp in history:
        ##                            default = 'default%s' % hn
        ##                            if 'Simple' in ht:
        ##                                pre += ['%s.' % hn]
        ##                            else:
        ##                                if 'Req' in ht:
        ##                                    pre += ['%s.value.' % hn]
        ##                                elif 'SemiOpt' in ht:
        ##                                    prel += ['%s.IsLoaded()' % hn]
        ##                                    pre += ['%s->' % hn]
        ##                                elif 'Opt' in ht:
        ##                                    prel += ['%s.IsLoaded()' % hn]
        ##                                    pre += ['%s->' % hn]
        ##                                elif 'Array' in ht:
        ##                                    pre += ['%s.' % hn]
        ##                                else:
        ##                                    pre += ['%s.value.' % hn]
        ##                    pres = ''.join(pre)
        ##                    if 'Req' not in type and 'Array' not in type:
        ##                        v += ['%sif(%s%s.IsLoaded())' % ('    ' * indent, pres, name,)]
        ##                    if len(vk) > 1:
        ##                        v += ['%s{' % ('    ' * (indent + 1),)]
        ##                    v += vk
        ##                    if len(vk) > 1:
        ##                        v += ['%s}' % ('    ' * (indent + 1),)]
        ##            if t == 'FORMID' or name == 'SCR_':
        ##                pre = ''
        ##                if len(history):
        ##                    for hn, ht, hp in history:
        ##                        if 'Simple' in ht:
        ##                            pre += '%s.' % hn
        ##                        else:
        ##                            if 'Req' in ht:
        ##                                pre += '%s.value.' % hn
        ##                            elif 'SemiOpt' in ht:
        ##                                pre += '%s->' % hn
        ##                            elif 'Opt' in ht:
        ##                                pre += '%s->' % hn
        ##                            elif 'Array' in ht:
        ##                                pre += '%s.' % hn
        ##                            else:
        ##                                pre += '%s.value.' % hn
        ##
        ##                    ln, lt, lp = history[-1]
        ##                    if 'Simple' in lt:
        ##                        if 'Req' not in lt:
        ##                            indent += 1
        ##                        if 'SemiOpt' in lt:
        ##                            v.append('%sop.Accept(*%svalue);' % ('    ' * indent, pre,))
        ##                        else:
        ##                            v.append('%sop.Accept(%svalue);' % ('    ' * indent, pre,))
        ##                        if 'Req' not in lt:
        ##                            indent -= 1
        ##                    elif 'Array' in lt:
        ##                        if lp:
        ##                            v.append('%sfor(UINT32 x = 0; x < %svalue.size(); x++)\n%sop.Accept(%svalue[x]->%s);' % ('    ' * (indent - 1),pre,'    ' * indent,pre, name))
        ##                        else:
        ##                            v.append('%sfor(UINT32 x = 0; x < %svalue.size(); x++)\n%sop.Accept(%svalue[x]);' % ('    ' * (indent - 1),pre,'    ' * indent,pre))
        ##                    elif name == 'SCR_':
        ##                        v.append('%sfor(UINT32 x = 0; x < %sSCR_.value.size(); x++)\n%sif(%sSCR_.value[x]->isSCRO)\n%sop.Accept(%sSCR_.value[x]->reference);' % ('    ' * indent,pre,'    ' * (indent + 1),pre, '    ' * (indent + 2),pre))
        ##                    else:
        ##                        v.append('%sop.Accept(%s%s);' % ('    ' * indent, pre, name,))
        ##                else:
        ##                    if 'Simple' in type:
        ##                        pre += '%s.' % name
        ##                        if 'SemiOpt' in type:
        ##                            v.append('%sop.Accept(%svalue);' % ('    ' * indent, pre,))
        ##                        else:
        ##                            v.append('%sop.Accept(&%svalue);' % ('    ' * indent, pre,))
        ##                    else:
        ##                        if 'Req' in type:
        ##                            pre += '%s.value.' % name
        ##                        elif 'SemiOpt' in type:
        ##                            pre += '%s->' % name
        ##                        elif 'Opt' in type:
        ##                            pre += '%s->' % name
        ##                        else:
        ##                            pre += '%s.value.' % name
        ##                        v.append('%sop.Accept(&%s%s);' % ('    ' * indent, pre, name,))
        ##        return v

    fidVars = []
    madeChanges = True
    fidVars = cl_vars
    while madeChanges:
        madeChanges = False
        fidVars = makeFids(fidVars)

    madeChanges = True
    def makeReads(vs, history=[]):
        global madeChanges, indent
        v = []
        for name, type, size, ip, vars in vs:
            t = type.strip(' *')
            s = len(vars)
            if s == 1 and vars[0][0] == '':
                s = 0
            if vars == modelSig:
                print 'in'
                inte = name[3]
                if inte == '2':
                    MODL = 'MOD2'
                    MODB = 'MO2B'
                    MODT = 'MO2T'
                    MODS = 'MO2S'
                    MODD = 'MO2D'
                elif inte == '3':
                    MODL = 'MOD3'
                    MODB = 'MO3B'
                    MODT = 'MO3T'
                    MODS = 'MO3S'
                    MODD = 'MO3D'
                elif inte == '4':
                    MODL = 'MOD4'
                    MODB = 'MO4B'
                    MODT = 'MO4T'
                    MODS = 'MO4S'
                    MODD = 'MO4D'
                else:                    
                    MODL = 'MODL'
                    MODB = 'MODB'
                    MODT = 'MODT'
                    MODS = 'MODS'
                    MODD = 'MODD'
                v.append('            case REV32(%s):\n                %s.Load();\n                %s->MODL.Read(buffer, subSize, curPos);\n                break;\n            case REV32(%s):\n                %s.Load();\n                %s->MODB.Read(buffer, subSize, curPos);\n                break;\n            case REV32(%s):\n                %s.Load();\n                %s->MODT.Read(buffer, subSize, curPos);\n                break;\n            case REV32(%s):\n                %s.Load();\n                %s->Textures.Read(buffer, subSize, curPos);\n                break;\n            case REV32(%s):\n                %s.Load();\n                %s->MODD.Read(buffer, subSize, curPos);\n                break;\n' % (MODL,n, n, MODB, n, n, MODT, n, n, MODS, n, n, MODD, n, n))
            elif s > 0:
                vk = makeReads(vars, history + [(name, type, ip)])
                if len(vk):
                    v += vk
                    continue
            if t in ('RawRecord', 'NonNullStringRecord', 'StringRecord') or t in recs:
                pre = []
                prel = []
                if len(history):
                    for hn, ht, hp in history:
                        if 'SemiOpt' in ht:
                            prel += ['%s.Load();' % hn]
                            pre += ['%s->' % hn]
                        elif 'Simple' in ht:
                            pre += ['%s.value.' % hn]
                        elif 'Opt' in ht:
                            prel += ['%s.Load();' % hn]
                            pre += ['%s->' % hn]

                loads = '\n                '.join(prel)
                vname = name
                if name == 'SLSD':
                    vname = 'VARS'
                    x = '            case REV32(%s):\n                %s\n                %s%s.value.push_back(new GENVARS);\n                %s%s.value.back()->SLSD.Read(buffer, subSize, curPos);\n                break;\n' % (name, loads, ''.join(pre), vname, ''.join(pre), vname)
                elif name == 'VARS':
                    continue
                elif name == 'SCVR':
                    vname = 'VARS'
                    x = '            case REV32(%s):\n                %s\n                if(%s%s.value.size() == 0)\n                    %s%s.value.push_back(new GENVARS);\n                %s%s.value.back()->SCVR.Read(buffer, subSize, curPos);\n                break;\n' % (name, loads, ''.join(pre), vname, ''.join(pre), vname, ''.join(pre), vname)
                elif name == 'SCR_':
                    vname = 'SCRO'
                    x = '            case REV32(%s):\n                %s\n                %s%s.Read(buffer, subSize, curPos);\n                %s%s.value.back()->isSCRO = true;\n                break;\n' % (vname, loads, ''.join(pre), name, ''.join(pre), name)
                    vname = 'SCRV'
                    x += '            case REV32(%s):\n                %s\n                %s%s.Read(buffer, subSize, curPos);\n                %s%s.value.back()->isSCRO = false;\n                break;\n' % (vname, loads, ''.join(pre), name, ''.join(pre), name)
                elif loads:
                    x = '            case REV32(%s):\n                %s\n                %s%s.Read(buffer, subSize, curPos);\n                break;\n' % (name, loads, ''.join(pre), vname)
                else:
                    x = '            case REV32(%s):\n                %s%s.Read(buffer, subSize, curPos);\n                break;\n' % (name, ''.join(pre), vname)
                if name == 'XPRD':
                    x += '            case REV32(XPPA):\n                //XPPA, Patrol Script Marker (Empty)\n                break;\n'
    ##            print x
                v.append(x)
        return v

    readVars = cl_vars
    madeChanges = True
    while madeChanges:
        madeChanges = False
        readVars = makeReads(readVars)

    if False:
        pass
        ##def makeFids(vars):
        ##    for _rec, type, n, s in vars:
        ##        if type:
        ##            ltype = False
        ##            if ' ' in type:
        ##                ltype = True
        ##                type = type[:type.find(' ')]
        ##            if type == 'FORMID':
        ##                if _rec is None:
        ##                    pre = pre.lstrip('.')
        ##                    if lrec:
        ##                        fids.append('    op.Accept(%s.value%s%s);\n' % (pre, lrec, n,))
        ##                    else:
        ##                        fids.append('    op.Accept(%s.value.%s);\n' % (pre, n,))
        ##                elif 'Simple' in _rec:
        ##                    if 'Req' in _rec:
        ##                        fids.append('    op.Accept(%s.value);\n' % n)
        ##                    else:
        ##                        fids.append('    if(%s.IsLoaded())\n        op.Accept(%s.value);\n' % (n,n))
        ##                elif 'Array' in _rec:
        ##                    fids.append('    for(UINT32 x = 0; x < %s.value.size(); x++)\n        op.Accept(%s.value[x]);\n' % (n,n))
        ##            elif type == 'FNVMODEL':
        ##                fids.append('    if(%s.IsLoaded())\n        {\n        for(UINT32 x = 0; x < %s->Textures.MODS.size(); x++)\n            op.Accept(%s->Textures.MODS[x]->texture);\n        }\n' % (n,n,n))
        ##            elif type == 'GENDESTRUCT':
        ##                fids.append('    if(Destructable.IsLoaded())\n        {\n        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)\n            {\n            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);\n            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);\n            }\n        }\n')
        ##            elif type == 'FNVCNTO':
        ##                fids.append('    for(UINT32 x = 0; x < CNTO.value.size(); ++x)\n        {\n        op.Accept(CNTO.value[x]->CNTO.value.item);\n        if(CNTO.value[x]->IsGlobal())\n            op.Accept(CNTO.value[x]->COED->globalOrRank);\n        }\n')
        ##            elif _rec and 'Array' in _rec:
        ##                lfids = fids
        ##                fids = []
        ##                strvars = str_vars.get(type, None)
        ##                if strvars is None:
        ##                    strvars = cl_vars.get(cltag + '::' + type, None)
        ##                    if strvars is None:
        ##                        print _rec, type, n, s
        ##                        raise
        ##                if ltype:
        ##                    getFids(strvars, pre+'.'+n, '[x]->')
        ##                else:
        ##                    getFids(strvars, pre+'.'+n, '[x].')
        ##                lfids.append('    for(UINT32 x = 0; x < %s.value.size(); x++)\n' % (n,))
        ##                if len(fids) > 1:
        ##                    lfids.append('        {\n')
        ##                for fid in fids:
        ##                    lfids.append('    ' + fid)
        ##                if len(fids) > 1:
        ##                    lfids.append('        }\n')
        ##                fids = lfids
        ##                lfids = []
        ##            else:
        ##                strvars = str_vars.get(type, None)
        ##                if strvars is None:
        ##                    strvars = cl_vars.get(cltag + '::' + type, None)
        ##                    if strvars is None:
        ##                        continue #It's not a struct or class, so we're not interested
        ##                getFids(strvars, pre+'.'+n, _rec)




    if True: #cpp generation
        f = open('%s.cpp' % cltag, 'w')
        f.write('/*\nGPL License and Copyright Notice ============================================\n This file is part of CBash.\n\n CBash is free software; you can redistribute it and/or\n modify it under the terms of the GNU General Public License\n as published by the Free Software Foundation; either version 2\n of the License, or (at your option) any later version.\n\n CBash is distributed in the hope that it will be useful,\n but WITHOUT ANY WARRANTY; without even the implied warranty of\n MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n GNU General Public License for more details.\n\n You should have received a copy of the GNU General Public License\n along with CBash; if not, write to the Free Software Foundation,\n Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.\n\n CBash copyright (C) 2010 Waruddar\n=============================================================================\n*/\n#include "..\\..\\Common.h"\n')
        f.write('#include "%s.h"\n\n' % cltag)
        f.write('namespace FNV\n{\n')
        for str, (tag, vars) in str_funcs.iteritems():
            if "::" in str:
                group = []
                groups = []
                lfunc = None
                didgroups = False
                for qual, func, fvars in vars:
                    if func == lfunc:
                        continue
                    if func == tag:
                        continue
                    if func == '~%s' % (tag):
                        continue
                    if func == '==':
                        continue
                    if func == '!=':
                        continue
                    lfunc = func
                    group += [(qual, func)]
                    if func[:3] == 'Set':
                        groups.append([func[-4:] == 'Type'] + group)
                        group = []
                for qual, func, fvars in vars:
                    svars = str_vars[qual][1]
                    if func == tag:
                        struct = '%s::%s():\n' % (qual, func)
                        body = ''
                        hadVars = False
                        for n, type, s, ip, ssvars in svars:
                            if ssvars:
                                pass #unimplemented
##                                raise "test"
                            if ip:
                                struct += '    %s(NULL),\n' % (n,)
                            elif s is None or s == 0:
                                hadVars = True
                                if type == 'FLOAT32':
                                    struct += '    %s(0.0f),\n' % (n,)
                                else:
                                    struct += '    %s(0),\n' % (n,)
                            else:
                                body += '    memset(&%s[0], 0x00, sizeof(%s));\n' % (n, n)
                        if hadVars:
                            struct = struct[:-2] + '\n'
                            hadVars = False
                        struct += '    {\n'
                        struct += body if len(body) > 1 else '    //\n'
                        struct += '    }\n\n'
                    elif func == '~%s' % (tag):
                        struct = '%s::%s()\n    {\n    //\n    }\n\n' % (qual, func)
                    elif func == '==':
                        struct = 'bool %s::operator ==(%s) const\n    {\n    return (' % (qual, fvars)
                        hadVars = False
                        v = []
                        for n, type, s, ip, ssvars in svars:
                            if ssvars:
                                pass #unimplemented
##                                raise "test"
                            if 'unused' in n.lower():
                                continue
                            if s is None or s == 0:
                                if ip:
                                    v += ['(%s != NULL && other.%s != NULL && *%s == *other.%s)' % (n, n, n, n)]
                                elif type == 'FLOAT32':
                                    v += ['AlmostEqual(%s,other.%s,2)' % (n, n)]
                                else:
                                    v += ['%s == other.%s' % (n, n)]
                            else:
                                if ip:
                                    v += ['(%s != NULL && other.%s != NULL)' % (n, n)]
                                for x in range(s):
                                    v += ['%s[%d] == other.%s[%d]' % (n, x, n, x)]
                        struct += ' &&\n            '.join(v) + ');\n'
                        struct += '    }\n\n'
                    elif func == '!=':
                        struct = 'bool %s::operator !=(%s) const\n    {\n    return !(*this == other);\n    }\n\n' % (qual, fvars)
                    elif groups:
                        if didgroups:
                            continue
                        for x, group in enumerate(groups):
                            isType = group[0]
                            dummy = '%sDummy%d' % (qual, x)
                            for qual, func in group[1:-2]:
                                if isType:
                                    stype = func[2:]
                                    f.write('bool %s::%s()\n    {\n    if(!%s.IsLoaded()) return false;\n    return %s->type == e%s;\n    }\n\nvoid %s::%s(bool value)\n    {\n    if(!%s.IsLoaded()) return;\n    %s->type = value ? e%s : e%s;\n    }\n\n' % (qual, func, dummy, dummy, stype, qual, func, dummy, dummy, stype, dummy))
                                else:
                                    f.write('bool %s::%s()\n    {\n    if(!%s.IsLoaded()) return false;\n    return (%s->flags & f%s) != 0;\n    }\n\nvoid %s::%s(bool value)\n    {\n    if(!%s.IsLoaded()) return;\n    %s->flags = value ? (%s->flags | f%s) : (%s->flags & ~f%s);\n    }\n\n' % (qual, func, dummy, dummy, func, qual, func, dummy, dummy, dummy, func, dummy, func))
                            qual, func = group[-2]
                            if isType:
                                f.write('bool %s::%s(UINT8 Type)\n    {\n    if(!%s.IsLoaded()) return false;\n    return %s->type == Type;\n    }\n\n' % (qual, func, dummy, dummy))
                            else:
                                f.write('bool %s::%s(UINT8 Mask, bool Exact)\n    {\n    if(!%s.IsLoaded()) return false;\n    return Exact ? ((%s->flags & Mask) == Mask) : ((%s->flags & Mask) != 0);\n    }\n\n' % (qual, func, dummy, dummy, dummy))
                            qual, func = group[-1]
                            if isType:
                                f.write('void %s::%s(UINT8 Type)\n    {\n    %s.Load();\n    %s->type = Type;\n    }\n\n' % (qual, func, dummy, dummy))
                            else:
                                f.write('void %s::%s(UINT8 Mask)\n    {\n    %s.Load();\n    %s->flags = Mask;\n    }\n\n' % (qual, func, dummy, dummy))
                        didgroups = True
                        continue
                    f.write(struct)
        f.write('%s::%s(unsigned char *_recData):\n    FNVRecord(_recData)\n    {\n    //\n    }\n\n' % (cltag, cltag))
        f.write('%s::%s(%s *srcRecord):\n    FNVRecord()\n    {\n    if(srcRecord == NULL)\n        return;\n\n    flags = srcRecord->flags;\n    formID = srcRecord->formID;\n    flagsUnk = srcRecord->flagsUnk;\n    formVersion = srcRecord->formVersion;\n    versionControl2[0] = srcRecord->versionControl2[0];\n    versionControl2[1] = srcRecord->versionControl2[1];\n\n    if(!srcRecord->IsChanged())\n        {\n        IsLoaded(false);\n        recData = srcRecord->recData;\n        return;\n        }\n\n' % (cltag, cltag, cltag))
        for topchunk in topchunks:
            f.write('    %s = srcRecord->%s;\n' % (topchunk, topchunk))
        f.write('    return;\n    }\n\n%s::~%s()\n    {\n    //\n    }\n\n' % (cltag, cltag))
        fids = []

        if len(fidVars):
            f.write('bool %s::VisitFormIDs(FormIDOp &op)\n    {\n    if(!IsLoaded())\n        return false;\n\n' % cltag)
            f.write(''.join(fidVars))
            f.write('\n    return op.Stop();\n    }\n\n')

        group = []
        groups = []
        lname = None
        for qual, name, args in cl_funcs:
            if name == lname:
                continue
            lname = name
            group += [name]
            if name[:3] == 'Set':
                groups.append([name[-4:] == 'Type'] + group)
                group = []
        for x, group in enumerate(groups):
            isType = group[0]
            dummy = 'Dummy%d' % x
            for func in group[1:-2]:
                if isType:
                    stype = func[2:]
                    f.write('bool %s::%s()\n    {\n    if(!%s.IsLoaded()) return false;\n    return %s->type == e%s;\n    }\n\nvoid %s::%s(bool value)\n    {\n    if(!%s.IsLoaded()) return;\n    %s->type = value ? e%s : e%s;\n    }\n\n' % (cltag, func, dummy, dummy, stype, cltag, func, dummy, dummy, stype, dummy))
                else:
                    f.write('bool %s::%s()\n    {\n    if(!%s.IsLoaded()) return false;\n    return (%s->flags & f%s) != 0;\n    }\n\nvoid %s::%s(bool value)\n    {\n    if(!%s.IsLoaded()) return;\n    %s->flags = value ? (%s->flags | f%s) : (%s->flags & ~f%s);\n    }\n\n' % (cltag, func, dummy, dummy, func, cltag, func, dummy, dummy, dummy, func, dummy, func))
            func = group[-2]
            if isType:
                f.write('bool %s::%s(UINT8 Type)\n    {\n    if(!%s.IsLoaded()) return false;\n    return %s->type == Type;\n    }\n\n' % (cltag, func, dummy, dummy))
            else:
                f.write('bool %s::%s(UINT8 Mask, bool Exact)\n    {\n    if(!%s.IsLoaded()) return false;\n    return Exact ? ((%s->flags & Mask) == Mask) : ((%s->flags & Mask) != 0);\n    }\n\n' % (cltag, func, dummy, dummy, dummy))
            func = group[-1]
            if isType:
                f.write('void %s::%s(UINT8 Type)\n    {\n    %s.Load();\n    %s->type = Type;\n    }\n\n' % (cltag, func, dummy, dummy))
            else:
                f.write('void %s::%s(UINT8 Mask)\n    {\n    %s.Load();\n    %s->flags = Mask;\n    }\n\n' % (cltag, func, dummy, dummy))

        f.write('UINT32 %s::GetType()\n    {\n    return REV32(%s);\n    }\n\nSTRING %s::GetStrType()\n    {\n    return "%s";\n    }\n\n' % (cltag, cltag[:4], cltag, cltag[:4]))
        f.write('SINT32 %s::ParseRecord(unsigned char *buffer, const UINT32 &recSize)\n    {\n    UINT32 subType = 0;\n    UINT32 subSize = 0;\n    UINT32 curPos = 0;\n    while(curPos < recSize){\n        _readBuffer(&subType, buffer, 4, curPos);\n        switch(subType)\n            {\n            case REV32(XXXX):\n                curPos += 2;\n                _readBuffer(&subSize, buffer, 4, curPos);\n                _readBuffer(&subType, buffer, 4, curPos);\n                curPos += 2;\n                break;\n            default:\n                subSize = 0;\n                _readBuffer(&subSize, buffer, 2, curPos);\n                break;\n            }\n        switch(subType)\n            {\n' % (cltag,))

        f.write(''.join(readVars))

        f.write('            default:\n                //printf("FileName = %%s\\n", FileName);\n                printf("  %s: %%08X - Unknown subType = %%04x\\n", formID, subType);\n                printf("  Size = %%i\\n", subSize);\n                printf("  CurPos = %%04x\\n\\n", curPos - 6);\n                curPos = recSize;\n                break;\n            }\n        };\n    return 0;\n    }\n\nSINT32 %s::Unload()\n    {\n    IsChanged(false);\n    IsLoaded(false);\n\n' % (cltag[:4],cltag))
        for topchunk in topchunks:
            f.write('    %s.Unload();\n' % (topchunk,))

        f.write('    return 1;\n    }\n\nSINT32 %s::WriteRecord(FileWriter &writer)\n    {\n' % cltag)
        for name, type, size, ip, vars in cl_vars:
            if vars == modelSig:
                f.write('    %s.Write(writer);\n' % name)
            elif type == 'GENDESTRUCT':
                f.write('    %s.Write(writer);\n' % name)
            else:
                f.write('    WRITE(%s);\n' % (name,))

        f.write('    return -1;\n    }\n\nbool %s::operator ==(const %s &other) const\n    {\n    return (' % (cltag, cltag))
        v = []
        for n, type, size, ip, vars in cl_vars:
            if type == 'StringRecord':
                if n in ISTRINGS:
                    v += ['%s.equalsi(other.%s)' % (n,n)]
                else:
                    v += ['%s.equals(other.%s)' % (n,n)]
            else:
                v += ['%s == other.%s' % (n,n)]
        f.write(' &&\n            '.join(v))
        f.write(');\n    }\n\nbool %s::operator !=(const %s &other) const\n    {\n    return !(*this == other);\n    }\n}' % (cltag, cltag))
        f.close()

    re_tern = re.compile('(return|\*FieldValues =) (.*?) \? (.*?) \: .*;')
    re_name = re.compile('//(.*?)$')
    def makeAttrApi(vs, history=[]):
        global madeChanges, indent
        attrs = []
        for name, type, size, ip, vars in vs:
            t = type.strip(' *')
            s = len(vars)
            if 'unused' in name.lower() and (size is None or size == 0):
                size = 1
            if s == 1 and vars[0][0] == '':
                s = 0
                t = vars[0][1]

            if vars == modelSig:
                inte = name[3]
                if inte == '2':
                    MODL = 'MOD2'
                    MODB = 'MO2B'
                    MODT = 'MO2T'
                    MODS = 'MO2S'
                    MODD = 'MO2D'
                elif inte == '3':
                    MODL = 'MOD3'
                    MODB = 'MO3B'
                    MODT = 'MO3T'
                    MODS = 'MO3S'
                    MODD = 'MO3D'
                elif inte == '4':
                    MODL = 'MOD4'
                    MODB = 'MO4B'
                    MODT = 'MO4T'
                    MODS = 'MO4S'
                    MODD = 'MO4D'
                else:                    
                    MODL = 'MODL'
                    MODB = 'MODB'
                    MODT = 'MODT'
                    MODS = 'MODS'
                    MODD = 'MODD'


                attrs.append(' //modPath\n')
                attrs.append('            return ISTRING_FIELD;\n')
                attrs.append(' //modb\n')
                attrs.append('            return FLOAT32_FIELD;\n')
                attrs.append(' //modt_p\n')
                attrs.append('            switch(WhichAttribute)\n')
                attrs.append('                {\n')
                attrs.append('                case 0: //fieldType\n')
                attrs.append('                    return UINT8_ARRAY_FIELD;\n')
                attrs.append('                case 1: //fieldSize\n')
                attrs.append('                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;\n')
                attrs.append('                default:\n')
                attrs.append('                    return UNKNOWN_FIELD;\n')
                attrs.append('                }\n')
                attrs.append('            return UNKNOWN_FIELD;\n')
                attrs.append(' //altTextures\n')
                attrs.append('            if(!MODL.IsLoaded())\n')
                attrs.append('                return UNKNOWN_FIELD;\n')
                attrs.append('\n')
                attrs.append('            if(ListFieldID == 0) //altTextures\n')
                attrs.append('                {\n')
                attrs.append('                switch(WhichAttribute)\n')
                attrs.append('                    {\n')
                attrs.append('                    case 0: //fieldType\n')
                attrs.append('                        return LIST_FIELD;\n')
                attrs.append('                    case 1: //fieldSize\n')
                attrs.append('                        return MODL->Textures.MODS.size();\n')
                attrs.append('                    default:\n')
                attrs.append('                        return UNKNOWN_FIELD;\n')
                attrs.append('                    }\n')
                attrs.append('                }\n')
                attrs.append('\n')
                attrs.append('            if(ListIndex >= MODL->Textures.MODS.size())\n')
                attrs.append('                return UNKNOWN_FIELD;\n')
                attrs.append('\n')
                attrs.append('            switch(ListFieldID)\n')
                attrs.append('                {\n')
                attrs.append('                case 1: //name\n')
                attrs.append('                    return STRING_FIELD;\n')
                attrs.append('                case 2: //texture\n')
                attrs.append('                    return FORMID_FIELD;\n')
                attrs.append('                case 3: //index\n')
                attrs.append('                    return SINT32_FIELD;\n')
                attrs.append('                default:\n')
                attrs.append('                    return UNKNOWN_FIELD;\n')
                attrs.append('                }\n')
                attrs.append('            return UNKNOWN_FIELD;\n')
                attrs.append(' //modelFlags\n')
                attrs.append('            return UINT8_FLAG_FIELD;\n')
            elif s > 0:
                vk = makeAttrApi(vars, history + [(name, type, ip)])
                if 'Array' in type:
                    topname, toptype, topip = name, type, ip
                    caseNum = 1
                    x = []
                    pre = []
                    prel = []
                    if len(history):
                        for hn, ht, hp in history:
                            if 'SemiOpt' in ht:
                                prel += ['%s.IsLoaded()' % hn]
                                pre += ['%s->' % hn]
                            elif 'Opt' in ht:
                                prel += ['%s.IsLoaded()' % hn]
                                pre += ['%s->' % hn]
                    loads = ' && '.join(prel)
                    pres = ''.join(pre)
                    attrs.append(' //%s\n' % (topname.lower(),))
                    if prel:
                        attrs.append('            if(!%s)\n' % (loads,))
                        attrs.append('                return UNKNOWN_FIELD;\n\n')
                    attrs.append('            if(ListFieldID == 0) //%s\n' % (topname.lower(),))
                    attrs.append('                {\n')
                    attrs.append('                switch(WhichAttribute)\n')
                    attrs.append('                    {\n')
                    attrs.append('                    case 0: //fieldType\n')
                    if topname == 'SCR_':
                        attrs.append('                        return FORMID_OR_UINT32_ARRAY_FIELD;\n')
                    else:
                        attrs.append('                        return LIST_FIELD;\n')
                    attrs.append('                    case 1: //fieldSize\n')
                    attrs.append('                        return (UINT32)%s%s.value.size();\n' % (pres, topname))
                    attrs.append('                    default:\n')
                    attrs.append('                        return UNKNOWN_FIELD;\n')
                    attrs.append('                    }\n')
                    attrs.append('                return UNKNOWN_FIELD;\n')
                    attrs.append('                }\n\n')
                    attrs.append('            if(ListIndex >= %s%s.value.size())\n' % (pres, topname))
                    attrs.append('                return UNKNOWN_FIELD;\n\n')
                    attrs.append('            switch(ListFieldID)\n')
                    attrs.append('                {\n')
                    usedNames = set()
                    for attr in vk:
                        if isinstance(attr, list):
                            attr = ''.join(attr)
                        inf = re_name.search(attr)
                        if inf:
                            name = inf.groups()[0]
                            try:
                                num = int(name[-1])
                                tname = name[:-1]
                            except:
                                num = 10
                                tname = name
                            while name in usedNames:
                                name = tname + `num`
                                num += 1
                            usedNames.add(name)
                                
                        if '//' in attr and 'case' not in attr:
                            x.append('                case %d: //%s\n' % (caseNum,name))
                            caseNum += 1
                        elif 'SCR_' == topname and caseNum == 2:
                            x.append('                    switch(WhichAttribute)\n')
                            x.append('                        {\n')
                            x.append('                        case 0: //fieldType\n')
                            x.append('                            return FORMID_OR_UINT32_FIELD;\n')
                            x.append('                        case 2: //WhichType\n')
                            x.append('                            return %sSCR_.value[ListIndex]->isSCRO ? FORMID_FIELD : UINT32_FIELD;\n' % (pres,))
                            x.append('                        default:\n')
                            x.append('                            return UNKNOWN_FIELD;\n')
                            x.append('                        }\n')
                            x.append('                    return UNKNOWN_FIELD;\n')
                        else:
                            tern = re_tern.search(attr)
                            if tern:
                                attr = attr[:attr.find('return')] + 'return %s;\n' % tern.groups()[2]
                            x.append('        ' + attr)
                    attrs += [x]
                    attrs.append('                default:\n')
                    attrs.append('                    return UNKNOWN_FIELD;\n')
                    attrs.append('                }\n')
                    attrs.append('            return UNKNOWN_FIELD;\n')
                else:
                    attrs += vk
            else:
                if name == 'EDID':
                    continue
                pre = []
                prel = []
                if len(history):
                    for hn, ht, hp in history:
                        if 'SemiOpt' in ht:
                            prel += ['%s.IsLoaded()' % hn]
                            pre += ['%s->' % hn]
                        elif 'Opt' in ht:
                            prel += ['%s.IsLoaded()' % hn]
                            pre += ['%s->' % hn]
                loads = ' && '.join(prel)
                pres = ''.join(pre)
                if 'StringRecord' in t:
                    attrs.append(' //%s\n' % (name,))
                    if name in ISTRINGS:
                        attrs.append('            return ISTRING_FIELD;\n')
                    else:
                        attrs.append('            return STRING_FIELD;\n')
                elif t == 'RawRecord':
                    if loads:
                        attrs.append(' //%s_p\n' % (name.lower(),))
                        attrs.append('            switch(WhichAttribute)\n')
                        attrs.append('                {\n')
                        attrs.append('                case 0: //fieldType\n')
                        attrs.append('                    return UINT8_ARRAY_FIELD;\n')
                        attrs.append('                case 1: //fieldSize\n')
                        attrs.append('                    return %s ? %s%s.GetSize() : 0;\n' % (loads, pres, name))
                        attrs.append('                default:\n')
                        attrs.append('                    return UNKNOWN_FIELD;\n')
                        attrs.append('                }\n')
                        attrs.append('            return UNKNOWN_FIELD;\n')
                    else:
                        attrs.append(' //%s_p\n' % (name.lower(),))
                        attrs.append('            switch(WhichAttribute)\n')
                        attrs.append('                {\n')
                        attrs.append('                case 0: //fieldType\n')
                        attrs.append('                    return UINT8_ARRAY_FIELD;\n')
                        attrs.append('                case 1: //fieldSize\n')
                        attrs.append('                    return %s%s.GetSize();\n' % (pres, name))
                        attrs.append('                default:\n')
                        attrs.append('                    return UNKNOWN_FIELD;\n')
                        attrs.append('                }\n')
                        attrs.append('            return UNKNOWN_FIELD;\n')
                elif t in types:
                    if size:
                        if loads:
                            attrs.append(' //%s\n' % (name,))
                            attrs.append('            switch(WhichAttribute)\n')
                            attrs.append('                {\n')
                            attrs.append('                case 0: //fieldType\n')
                            attrs.append('                    return %s_ARRAY_FIELD;\n' % (t,))
                            attrs.append('                case 1: //fieldSize\n')
                            attrs.append('                    return %s ? %d : 0;\n' % (loads, size))
                            attrs.append('                default:\n')
                            attrs.append('                    return UNKNOWN_FIELD;\n')
                            attrs.append('                }\n')
                            attrs.append('            return UNKNOWN_FIELD;\n')
                        else:
                            attrs.append(' //%s\n' % (name,))
                            attrs.append('            switch(WhichAttribute)\n')
                            attrs.append('                {\n')
                            attrs.append('                case 0: //fieldType\n')
                            attrs.append('                    return %s_ARRAY_FIELD;\n' % (t,))
                            attrs.append('                case 1: //fieldSize\n')
                            attrs.append('                    return %d;\n' % (size,))
                            attrs.append('                default:\n')
                            attrs.append('                    return UNKNOWN_FIELD;\n')
                            attrs.append('                }\n')
                            attrs.append('            return UNKNOWN_FIELD;\n')
                    elif 'Array' in t:
                        attrs.append(' //%s\n' % (name,))
                        attrs.append('            switch(WhichAttribute)\n')
                        attrs.append('                {\n')
                        attrs.append('                case 0: //fieldType\n')
                        attrs.append('                    return %s_ARRAY_FIELD;\n' % (t,))
                        attrs.append('                case 1: //fieldSize\n')
                        attrs.append('                    return %s.value.size();\n' % (name,))
                        attrs.append('                default:\n')
                        attrs.append('                    return UNKNOWN_FIELD;\n')
                        attrs.append('                }\n')
                        attrs.append('            return UNKNOWN_FIELD;\n')
                    else:
                        attrs.append(' //%s\n' % (name,))
                        if 'flag' in name:
                            t += '_FLAG'
                        attrs.append('            return %s_FIELD;\n' % (t,))
                else:
                    print "111", name, type, size, ip, vars
        return attrs

    def makeGetApi(vs, history=[]):
        global madeChanges, indent
        attrs = []
        for name, type, size, ip, vars in vs:
            t = type.strip(' *')
            s = len(vars)
            if 'unused' in name.lower() and (size is None or size == 0):
                size = 1
            if s == 1 and vars[0][0] == '':
                s = 0
                t = vars[0][1]
            if vars == modelSig:
                inte = name[3]
                if inte == '2':
                    MODL = 'MOD2'
                    MODB = 'MO2B'
                    MODT = 'MO2T'
                    MODS = 'MO2S'
                    MODD = 'MO2D'
                elif inte == '3':
                    MODL = 'MOD3'
                    MODB = 'MO3B'
                    MODT = 'MO3T'
                    MODS = 'MO3S'
                    MODD = 'MO3D'
                elif inte == '4':
                    MODL = 'MOD4'
                    MODB = 'MO4B'
                    MODT = 'MO4T'
                    MODS = 'MO4S'
                    MODD = 'MO4D'
                else:                    
                    MODL = 'MODL'
                    MODB = 'MODB'
                    MODT = 'MODT'
                    MODS = 'MODS'
                    MODD = 'MODD'


                attrs.append(' //modPath\n')
                attrs.append('            return %s.IsLoaded() ? %s->MODL.value : NULL;\n' % (MODL,MODL))
                attrs.append(' //modb\n')
                attrs.append('            return %s.IsLoaded() ? &%s->MODB.value : NULL;\n' % (MODL,MODL))
                attrs.append(' //modt_p\n')
                attrs.append('            *FieldValues = %s.IsLoaded() ? %s->MODT.value : NULL;\n' % (MODL,MODL))
                attrs.append('            return NULL;\n')
                attrs.append(' //altTextures\n')
                attrs.append('            if(!%s.IsLoaded())\n' % (MODL,))
                attrs.append('                return NULL;\n')
                attrs.append('\n')
                attrs.append('            if(ListIndex >= %s->Textures.MODS.size())\n' % (MODL,))
                attrs.append('                return NULL;\n')
                attrs.append('\n')
                attrs.append('            switch(ListFieldID)\n')
                attrs.append('                {\n')
                attrs.append('                case 1: //name\n')
                attrs.append('                    return %s->Textures.MODS[ListIndex]->name;\n' % (MODL,))
                attrs.append('                case 2: //texture\n')
                attrs.append('                    return &%s->Textures.MODS[ListIndex]->texture;\n' % (MODL,))
                attrs.append('                case 3: //index\n')
                attrs.append('                    return &%s->Textures.MODS[ListIndex]->index;\n' % (MODL,))
                attrs.append('                default:\n')
                attrs.append('                    return NULL;\n')
                attrs.append('                }\n')
                attrs.append('            return NULL;\n')
                attrs.append(' //modelFlags\n')
                attrs.append('            return %s.IsLoaded() ? &%s->MODD.value : NULL;\n' % (MODL,MODL))
            elif s > 0:
                vk = makeGetApi(vars, history + [(name, type, ip)])
                if 'Array' in type:
                    topname, toptype, topip = name, type, ip
                    caseNum = 1
                    x = []
                    pre = []
                    prel = []
                    if len(history):
                        for hn, ht, hp in history:
                            if 'SemiOpt' in ht:
                                prel += ['%s.IsLoaded()' % hn]
                                pre += ['%s->' % hn]
                            elif 'Opt' in ht:
                                prel += ['%s.IsLoaded()' % hn]
                                pre += ['%s->' % hn]
                    loads = ' && '.join(prel)
                    pres = ''.join(pre)
                    attrs.append(' //%s\n' % (topname.lower(),))
                    if 'SCR_' == topname:
                            if loads:
                                attrs.append('            if(!%s)\n' %(loads,))
                                attrs.append('                {\n')
                                attrs.append('                *FieldValues = NULL;\n')
                                attrs.append('                return NULL;\n')
                                attrs.append('                }\n')
                            attrs.append('            for(UINT32 x = 0; x < %sSCR_.value.size(); ++x)\n' % (pres,))
                            attrs.append('                ((FORMIDARRAY)FieldValues)[x] = %sSCR_.value[x]->reference;\n' % (pres,))
                            attrs.append('            return NULL;\n')
                    else:
                        if prel:
                            attrs.append('            if(!%s)\n' % (loads,))
                            attrs.append('                return NULL;\n\n')
                        attrs.append('            if(ListIndex >= %s%s.value.size())\n' % (pres, topname))
                        attrs.append('                return NULL;\n\n')
                        attrs.append('            switch(ListFieldID)\n')
                        attrs.append('                {\n')
                        usedNames = set()
                        for attr in vk:
                            if isinstance(attr, list):
                                attr = ''.join(attr)
                            inf = re_name.search(attr)
                            if inf:
                                name = inf.groups()[0]
                                try:
                                    num = int(name[-1])
                                    tname = name[:-1]
                                except:
                                    num = 10
                                    tname = name
                                while name in usedNames:
                                    name = tname + `num`
                                    num += 1
                                usedNames.add(name)
                            if '//' in attr and 'case' not in attr:
                                x.append('                case %d: //%s\n' % (caseNum,name))
                                caseNum += 1
                            else:
                                tern = re_tern.search(attr)
                                if tern:
                                    if topip:
                                        attr = attr[:attr.rfind(topname) + len(topname)] + '.value[ListIndex]->' + attr[attr.rfind(topname) + len(topname) + 1:]
                                    else:
                                        attr = attr[:attr.rfind(topname) + len(topname)] + '.value[ListIndex].' + attr[attr.rfind(topname) + len(topname) + 1:]
                                    tern = re_tern.search(attr)
                                    l = attr.find('return')
                                    if l > 0:
                                        attr = attr[:attr.find('return')] + 'return %s;\n' % tern.groups()[2]
                                    else:
                                        l = attr.find('*FieldValues')
                                        if l > 0:
                                            attr = attr[:attr.find('*FieldValues')] + '*FieldValues = %s;\n' % tern.groups()[2]
                                    
                                x.append('        ' + attr)
                        attrs += [x]
                        attrs.append('                default:\n')
                        attrs.append('                    return NULL;\n')
                        attrs.append('                }\n')
                        attrs.append('            return NULL;\n')
                else:
                    attrs += vk
            else:
                if name == 'EDID':
                    continue
                pre = []
                prel = []
                if len(history):
                    for hn, ht, hp in history:
                        if 'Simple' in ht:
                            pre += ['%s.' % hn]
                        else:
                            if 'Req' in ht:
                                pre += ['%s.value.' % hn]
                            elif 'SemiOpt' in ht:
                                prel += ['%s.IsLoaded()' % hn]
                                pre += ['%s->' % hn]
                            elif 'Opt' in ht:
                                prel += ['%s.IsLoaded()' % hn]
                                pre += ['%s->' % hn]
                            elif 'Array' in ht:
                                prel += ['%s.IsLoaded()' % hn]
                                pre += ['%s.' % hn]
                            else:
                                pre += ['%s.value.' % hn]
                loads = ' && '.join(prel)
                pres = ''.join(pre)
                if 'StringRecord' in t:
                    attrs.append(' //%s\n' % (name,))
                    if loads:
                        attrs.append('            return %s ? %s%s.value : NULL;\n' % (loads, pres, name))
                    else:
                        attrs.append('            return %s%s.value;\n' % (pres, name))
                elif t == 'RawRecord':
                    attrs.append(' //%s_p\n' % (name.lower(),))
                    if loads:
                        attrs.append('            *FieldValues = %s ? %s%s.value : NULL;\n' % (loads, pres, name))
                    else:
                        attrs.append('            *FieldValues = %s%s.value;\n' % (pres, name))
                    attrs.append('            return NULL;\n')
                elif t in types:
                    if size:
                        attrs.append(' //%s\n' % (name,))
                        if 'UINT8' == type:
                            if loads:
                                if size > 1:
                                    attrs.append('            *FieldValues = %s ? &%s%s[0] : NULL;\n' % (loads, pres, name))
                                else:
                                    attrs.append('            *FieldValues = %s ? &%s%s : NULL;\n' % (loads, pres, name))
                            else:
                                if size > 1:
                                    attrs.append('            *FieldValues = &%s%s[0];\n' % (pres, name))
                                else:
                                    attrs.append('            *FieldValues = &%s%s;\n' % (pres, name))
                            attrs.append('            return NULL;\n')
                        else:
                            if loads:
                                if size > 1:
                                    attrs.append('            return %s ? &%s%s[0] : NULL;\n' % (loads, pres, name))
                                else:
                                    attrs.append('            return %s ? &%s%s : NULL;\n' % (loads, pres, name))
                            else:
                                if size > 1:
                                    attrs.append('            return &%s%s[0];\n' % (pres, name))
                                else:
                                    attrs.append('            return &%s%s;\n' % (pres, name))
                    elif 'Array' in t:
                        attrs.append(' //%s\n' % (name,))
                        attrs.append('            return UNKNOWN_FIELD;\n')
                    else:
                        attrs.append(' //%s\n' % (name,))
                        if 'Simple' in type:
                            pres += '%s.' % name
                            if 'SemiOpt' in type:
                                if loads:
                                    attrs.append('            return %s ? %svalue : NULL;\n' % (loads, pres,))
                                else:
                                    attrs.append('            return %svalue;\n' % (pres,))
                            else:
                                if loads:
                                    attrs.append('            return %s ? &%svalue : NULL;\n' % (loads, pres,))
                                else:
                                    attrs.append('            return &%svalue;\n' % (pres,))
                        else:
                            if loads:
                                attrs.append('            return %s ? &%s%s : NULL;\n' % (loads, pres, name,))
                            else:
                                attrs.append('            return &%s%s;\n' % (pres, name,))
                else:
                    print "111", name, type, size, ip, vars
        return attrs

    def makeSetApi(vs, history=[]):
        global madeChanges, indent
        attrs = []
        for name, type, size, ip, vars in vs:
            t = type.strip(' *')
            s = len(vars)
            if 'unused' in name.lower() and (size is None or size == 0):
                size = 1
            if s == 1 and vars[0][0] == '':
                s = 0
                t = vars[0][1]
            if vars == modelSig:
                inte = name[3]
                if inte == '2':
                    MODL = 'MOD2'
                    MODB = 'MO2B'
                    MODT = 'MO2T'
                    MODS = 'MO2S'
                    MODD = 'MO2D'
                elif inte == '3':
                    MODL = 'MOD3'
                    MODB = 'MO3B'
                    MODT = 'MO3T'
                    MODS = 'MO3S'
                    MODD = 'MO3D'
                elif inte == '4':
                    MODL = 'MOD4'
                    MODB = 'MO4B'
                    MODT = 'MO4T'
                    MODS = 'MO4S'
                    MODD = 'MO4D'
                else:                    
                    MODL = 'MODL'
                    MODB = 'MODB'
                    MODT = 'MODT'
                    MODS = 'MODS'
                    MODD = 'MODD'

                attrs.append(' //modPath\n')
                attrs.append('            %s.Load();\n' % (MODL,))
                attrs.append('            %s->MODL.Copy((STRING)FieldValue);\n' % (MODL,))
                attrs.append('            break;\n')
                attrs.append(' //modb\n')
                attrs.append('            %s.Load();\n' % (MODL,))
                attrs.append('            %s->MODB.value = *(FLOAT32 *)FieldValue;\n' % (MODL,))
                attrs.append('            break;\n')
                attrs.append(' //modt_p\n')
                attrs.append('            %s.Load();\n' % (MODL,))
                attrs.append('            %s->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);\n' % (MODL,))
                attrs.append('            break;\n')
                attrs.append(' //altTextures\n')
                attrs.append('            %s.Load();\n' % (MODL,))
                attrs.append('            if(ListFieldID == 0) //altTexturesSize\n')
                attrs.append('                {\n')
                attrs.append('                %s->Textures.resize(ArraySize);\n' % (MODL,))
                attrs.append('                return false;\n')
                attrs.append('                }\n')
                attrs.append('\n')
                attrs.append('            if(ListIndex >= %s->Textures.MODS.size())\n' % (MODL,))
                attrs.append('                break;\n')
                attrs.append('\n')
                attrs.append('            switch(ListFieldID)\n')
                attrs.append('                {\n')
                attrs.append('                case 1: //name\n')
                attrs.append('                    delete []%s->Textures.MODS[ListIndex]->name;\n' % (MODL,))
                attrs.append('                    %s->Textures.MODS[ListIndex]->name = NULL;\n' % (MODL,))
                attrs.append('                    if(FieldValue != NULL)\n')
                attrs.append('                        {\n')
                attrs.append('                        ArraySize = (UINT32)strlen((STRING)FieldValue) + 1;\n')
                attrs.append('                        %s->Textures.MODS[ListIndex]->name = new char[ArraySize];\n' % (MODL,))
                attrs.append('                        strcpy_s(%s->Textures.MODS[ListIndex]->name, ArraySize, (STRING)FieldValue);\n' % (MODL,))
                attrs.append('                        }\n')
                attrs.append('                    break;\n')
                attrs.append('                case 2: //texture\n')
                attrs.append('                    %s->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;\n' % (MODL,))
                attrs.append('                    return true;\n')
                attrs.append('                case 3: //index\n')
                attrs.append('                    %s->Textures.MODS[ListIndex]->index = *(SINT32 *)FieldValue;\n' % (MODL,))
                attrs.append('                    break;\n')
                attrs.append('                default:\n')
                attrs.append('                    break;\n')
                attrs.append('                }\n')
                attrs.append('            break;\n')
                attrs.append(' //modelFlags\n')
                attrs.append('            %s.Load();\n' % (MODL,))
                attrs.append('            %s->SetFlagMask(*(UINT8 *)FieldValue);\n' % (MODL,))
                attrs.append('            break;\n')
                    
            elif s > 0:
                vk = makeSetApi(vars, history + [(name, type, ip)])
                if 'Array' in type:
                    topname, toptype, topip = name, type, ip
                    caseNum = 1
                    x = []
                    pre = []
                    prel = []
                    if len(history):
                        for hn, ht, hp in history:
                            if 'SemiOpt' in ht:
                                prel += ['%s.Load();' % hn]
                                pre += ['%s->' % hn]
                            elif 'Opt' in ht:
                                prel += ['%s.Load();' % hn]
                                pre += ['%s->' % hn]
                    loads = '\n                '.join(prel)
                    pres = ''.join(pre)
                    attrs.append(' //%s\n' % (topname.lower(),))
                    if prel:
                        attrs.append('            %s\n' % (loads,))
                    attrs.append('            if(ListFieldID == 0) //%sSize\n' % (topname.lower(),))
                    attrs.append('                {\n')
                    attrs.append('                %s%s.resize(ArraySize);\n' % (pres, topname))
                    attrs.append('                return false;\n')
                    attrs.append('                }\n\n')
                    attrs.append('            if(ListIndex >= %s%s.value.size())\n' % (pres, topname))
                    attrs.append('                break;\n\n')
                    attrs.append('            switch(ListFieldID)\n')
                    attrs.append('                {\n')
                    usedNames = set()
                    for attr in vk:
                        if isinstance(attr, list):
                            attr = ''.join(attr)
                        did = False
                        for pre in prel:
                            if pre in attr:
                                did = True
                                break
                        if did: continue                            

                        inf = re_name.search(attr)
                        if inf:
                            name = inf.groups()[0]
                            try:
                                num = int(name[-1])
                                tname = name[:-1]
                            except:
                                num = 10
                                tname = name
                            while name in usedNames:
                                name = tname + `num`
                                num += 1
                            usedNames.add(name)
                        if '//' in attr and 'case' not in attr:
                            x.append('                case %d: //%s\n' % (caseNum,name))
                            caseNum += 1
                        elif 'SCR_' == topname and caseNum == 2:
                            if 'break' in attr:
                                continue
                            x.append('                    //Borrowing ArraySize to flag if the new value is a formID\n')
                            x.append('                    %sSCR_.value[ListIndex]->reference = *(UINT32 *)FieldValue;\n' %( pres,))
                            x.append('                    %sSCR_.value[ListIndex]->isSCRO = ArraySize ? true : false;\n' %( pres,))
                            x.append('                    return ArraySize != 0;\n')
                        else:
                            rf = attr.rfind(topname)
                            if rf > 0:
                                if topip:
                                    attr = attr[:attr.rfind(topname) + len(topname)] + '.value[ListIndex]->' + attr[attr.rfind(topname) + len(topname) + 1:]
                                else:
                                    attr = attr[:attr.rfind(topname) + len(topname)] + '.value[ListIndex].' + attr[attr.rfind(topname) + len(topname) + 1:]
                                
                            x.append('        ' + attr)
                    attrs += [x]
                    attrs.append('                default:\n')
                    attrs.append('                    break;\n')
                    attrs.append('                }\n')
                    attrs.append('            break;\n')
                else:
                    attrs += vk
            else:
                if name == 'EDID':
                    continue
                pre = []
                prel = []
                if len(history):
                    for hn, ht, hp in history:
                        if 'Simple' in ht:
                            pre += ['%s.' % hn]
                        else:
                            if 'Req' in ht:
                                pre += ['%s.value.' % hn]
                            elif 'SemiOpt' in ht:
                                prel += ['%s.Load();' % hn]
                                pre += ['%s->' % hn]
                            elif 'Opt' in ht:
                                prel += ['%s.Load();' % hn]
                                pre += ['%s->' % hn]
                            elif 'Array' in ht:
                                pre += ['%s.' % hn]
                            else:
                                pre += ['%s.value.' % hn]
                pres = ''.join(pre)
                if 'StringRecord' in t:
                    attrs.append(' //%s\n' % (name,))
                    for pre in prel:
                        attrs.append('            %s\n' % (pre,))
                    attrs.append('            %s%s.Copy((STRING)FieldValue);\n' % (pres, name))
                    attrs.append('            break;\n')
                elif t == 'RawRecord':
                    attrs.append(' //%s_p\n' % (name.lower(),))
                    for pre in prel:
                        attrs.append('            %s\n' % (pre,))
                    attrs.append('            %s%s.Copy((UINT8ARRAY)FieldValue, ArraySize);\n' % (pres, name))
                    attrs.append('            break;\n')
                elif t in types:
                    if size:
                        attrs.append(' //%s\n' % (name,))
                        if 'UINT8' == type:
                            attrs.append('            if(ArraySize != %d)\n' % (size,))
                            attrs.append('                break;\n')
                            for pre in prel:
                                attrs.append('            %s\n' % (pre,))
                            if size > 1:
                                for z in range(size):
                                    attrs.append('            %s%s[%d] = ((UINT8ARRAY)FieldValue)[%d];\n' % (pres, name, z, z))
                            else:
                                attrs.append('            %s%s = ((UINT8ARRAY)FieldValue)[0];\n' % (pres, name))
                            attrs.append('            break;\n')
                        else:
                            attrs.append('            if(ArraySize != %d)\n' % (size,))
                            attrs.append('                break;\n')
                            for pre in prel:
                                attrs.append('            %s\n' % (pre,))
                            if size > 1:
                                for z in range(size):
                                    attrs.append('            %s%s[%d] = ((%sARRAY)FieldValue)[%d];\n' % (pres, name, z, type, z))
                            else:
                                attrs.append('            %s%s = ((%sARRAY)FieldValue)[0];\n' % (pres, name, type))
                            attrs.append('            break;\n')
                    elif 'Array' in t:
                        attrs.append(' //%s\n' % (name,))
                        attrs.append('            return UNKNOWN_FIELD;\n')
                    else:
                        attrs.append(' //%s\n' % (name,))
                        for pre in prel:
                            attrs.append('            %s\n' % (pre,))
                        if 'Simple' in type:
                            pres += '%s.' % name
                            if 'SemiOpt' in type:
                                attrs.append('            *%svalue = *(%s *)FieldValue;\n' % (pres, t))
                            else:
                                attrs.append('            %svalue = *(%s *)FieldValue;\n' % (pres, t))
                        else:
                            attrs.append('            %s%s = *(%s *)FieldValue;\n' % (pres, name, t))
                        if t == 'FORMID':
                            attrs.append('            return true;\n')
                        else:
                            attrs.append('            break;\n')
                else:
                    print "111", name, type, size, ip, vars
        return attrs

    def makeDelApi(vs, history=[]):
        global madeChanges, indent
        attrs = []
        for name, type, size, ip, vars in vs:
            t = type.strip(' *')
            s = len(vars)
            if 'unused' in name.lower() and (size is None or size == 0):
                size = 1
            if s == 1 and vars[0][0] == '':
                s = 0
                t = vars[0][1]
            if vars == modelSig:
                inte = name[3]
                if inte == '2':
                    MODL = 'MOD2'
                    MODB = 'MO2B'
                    MODT = 'MO2T'
                    MODS = 'MO2S'
                    MODD = 'MO2D'
                elif inte == '3':
                    MODL = 'MOD3'
                    MODB = 'MO3B'
                    MODT = 'MO3T'
                    MODS = 'MO3S'
                    MODD = 'MO3D'
                elif inte == '4':
                    MODL = 'MOD4'
                    MODB = 'MO4B'
                    MODT = 'MO4T'
                    MODS = 'MO4S'
                    MODD = 'MO4D'
                else:                    
                    MODL = 'MODL'
                    MODB = 'MODB'
                    MODT = 'MODT'
                    MODS = 'MODS'
                    MODD = 'MODD'

                attrs.append(' //modPath\n')
                attrs.append('            if(%s.IsLoaded())\n' % (MODL,))
                attrs.append('                %s->MODL.Unload();\n' % (MODL,))
                attrs.append('            return;\n')
                attrs.append(' //modb\n')
                attrs.append('            if(%s.IsLoaded())\n' % (MODL,))
                attrs.append('                %s->MODB.Unload();\n' % (MODL,))
                attrs.append('            return;\n')
                attrs.append(' //modt_p\n')
                attrs.append('            if(%s.IsLoaded())\n' % (MODL,))
                attrs.append('                %s->MODT.Unload();\n' % (MODL,))
                attrs.append('            return;\n')
                attrs.append(' //altTextures\n')
                attrs.append('            if(%s.IsLoaded())\n' % (MODL,))
                attrs.append('                {\n')
                attrs.append('                if(ListFieldID == 0) //altTextures\n')
                attrs.append('                    {\n')
                attrs.append('                    %s->Textures.Unload();\n' % (MODL,))
                attrs.append('                    return;\n')
                attrs.append('                    }\n')
                attrs.append('\n')
                attrs.append('                if(ListIndex >= %s->Textures.MODS.size())\n' % (MODL,))
                attrs.append('                    return;\n')
                attrs.append('\n')
                attrs.append('                switch(ListFieldID)\n')
                attrs.append('                    {\n')
                attrs.append('                    case 1: //name\n')
                attrs.append('                        delete []%s->Textures.MODS[ListIndex]->name;\n' % (MODL,))
                attrs.append('                        %s->Textures.MODS[ListIndex]->name = NULL;\n' % (MODL,))
                attrs.append('                        return;\n')
                attrs.append('                    case 2: //texture\n')
                attrs.append('                        %s->Textures.MODS[ListIndex]->texture = defaultMODS.texture;\n' % (MODL,))
                attrs.append('                        return;\n')
                attrs.append('                    case 3: //index\n')
                attrs.append('                        %s->Textures.MODS[ListIndex]->index = defaultMODS.index;\n' % (MODL,))
                attrs.append('                        return;\n')
                attrs.append('                    default:\n')
                attrs.append('                        return;\n')
                attrs.append('                    }\n')
                attrs.append('                }\n')
                attrs.append('            return;\n')
                attrs.append(' //modelFlags\n')
                attrs.append('            if(%s.IsLoaded())\n' % (MODL,))
                attrs.append('                %s->MODD.Unload();\n' % (MODL,))
                attrs.append('            return;\n')
            elif s > 0:
                vk = makeDelApi(vars, history + [(name, type, ip)])
                if 'Array' in type:
                    topname, toptype, topip = name, type, ip
                    caseNum = 1
                    x = []
                    pre = []
                    prel = []
                    if len(history):
                        for hn, ht, hp in history:
                            default = 'default%s' % hn
                            if 'Simple' in ht:
                                pre += ['%s.' % hn]
                            else:
                                if 'Req' in ht:
                                    pre += ['%s.value.' % hn]
                                elif 'SemiOpt' in ht:
                                    prel += ['%s.IsLoaded()' % hn]
                                    pre += ['%s->' % hn]
                                elif 'Opt' in ht:
                                    prel += ['%s.IsLoaded()' % hn]
                                    pre += ['%s->' % hn]
                                elif 'Array' in ht:
                                    pre += ['%s.' % hn]
                                else:
                                    pre += ['%s.value.' % hn]
                    loads = ' && '.join(prel)
                    pres = ''.join(pre)
                    attrs.append(' //%s\n' % (topname.lower(),))
                    if prel:
                        if '&&' in loads:
                            attrs.append('            if(!(%s))\n' % (loads,))
                        else:
                            attrs.append('            if(!%s)\n' % (loads,))
                        attrs.append('                return;\n\n')
                    attrs.append('            if(ListFieldID == 0) //%sSize\n' % (topname.lower(),))
                    attrs.append('                {\n')
                    attrs.append('                %s%s.Unload();\n' % (pres, topname))
                    attrs.append('                return;\n')
                    attrs.append('                }\n\n')
                    attrs.append('            if(ListIndex >= %s%s.value.size())\n' % (pres, topname))
                    attrs.append('                return;\n\n')
                    attrs.append('            switch(ListFieldID)\n')
                    attrs.append('                {\n')
                    usedNames = set()
                    did = False
                    did2 = False
                    for attr in vk:
                        if isinstance(attr, list):
                            attr = ''.join(attr)
                        did = False
                        for pre in prel:
                            if pre in attr:
                                did = True
                                did2 = True
                                break
                        if did: continue
                        if did2:
                            if '{' in attr:
                                continue
                            if '}' in attr:
                                continue
                            if 'return' in attr:
                                did2 = False
                            else:
                                attr = attr[4:]
                        inf = re_name.search(attr)
                        if inf:
                            name = inf.groups()[0]
                            try:
                                num = int(name[-1])
                                tname = name[:-1]
                            except:
                                num = 10
                                tname = name
                            while name in usedNames:
                                name = tname + `num`
                                num += 1
                            usedNames.add(name)
                        if '//' in attr and 'case' not in attr:
                            x.append('                case %d: //%s\n' % (caseNum,name))
                            caseNum += 1
                        elif 'SCR_' == topname and caseNum == 2:
                            if 'return' in attr:
                                continue
                            x.append('                    %sSCR_.value[ListIndex]->reference = defaultSCR_.reference;\n' % (pres,))
                            x.append('                    %sSCR_.value[ListIndex]->isSCRO = defaultSCR_.isSCRO;\n' % (pres,))
                            x.append('                    return;\n')
                        else:
                            rf = attr.rfind(topname)
                            if rf > 0:
                                if topip:
                                    attr = attr[:attr.find(topname) + len(topname)] + '.value[ListIndex]->' + attr[attr.find(topname) + len(topname) + 1:]
                                else:
                                    attr = attr[:attr.find(topname) + len(topname)] + '.value[ListIndex].' + attr[attr.find(topname) + len(topname) + 1:]
                                
                            x.append('        ' + attr)
                    attrs += [x]
                    attrs.append('                default:\n')
                    attrs.append('                    return;\n')
                    attrs.append('                }\n')
                    attrs.append('            return;\n')
                else:
                    attrs += vk
            else:
                if name == 'EDID':
                    continue
                pre = []
                prel = []
                default = 'default%s' % name
                if len(history):
                    for hn, ht, hp in history:
                        default = 'default%s' % hn
                        if 'Simple' in ht:
                            pre += ['%s.' % hn]
                        else:
                            if 'Req' in ht:
                                pre += ['%s.value.' % hn]
                            elif 'SemiOpt' in ht:
                                prel += ['%s.IsLoaded()' % hn]
                                pre += ['%s->' % hn]
                            elif 'Opt' in ht:
                                prel += ['%s.IsLoaded()' % hn]
                                pre += ['%s->' % hn]
                            elif 'Array' in ht:
                                pre += ['%s.' % hn]
                            else:
                                pre += ['%s.value.' % hn]
                pres = ''.join(pre)
                loads = ' && '.join(prel)
                if 'StringRecord' in t:
                    attrs.append(' //%s\n' % (name,))
                    if loads:
                        attrs.append('            if(%s)\n' % (loads,))
                        attrs.append('                %s%s.Unload();\n' % (pres, name))
                    else:
                        attrs.append('            %s%s.Unload();\n' % (pres, name))
                    attrs.append('            return;\n')
                elif t == 'RawRecord':
                    attrs.append(' //%s_p\n' % (name.lower(),))
                    if loads:
                        attrs.append('            if(%s)\n' % (loads,))
                        attrs.append('                %s%s.Unload();\n' % (pres, name))
                    else:
                        attrs.append('            %s%s.Unload();\n' % (pres, name))
                    attrs.append('            return;\n')
                elif 'Simple' in type:
                    attrs.append(' //%s\n' % (name,))
                    if loads:
                        attrs.append('            if(%s)\n' % (loads,))
                        attrs.append('                %s%s.Unload();\n' % (pres, name))
                    else:
                        attrs.append('            %s%s.Unload();\n' % (pres, name))
                    attrs.append('            return;\n')
                elif t in types:
                    if size:
                        attrs.append(' //%s\n' % (name,))
                        if size > 1:
                            if loads:
                                attrs.append('            if(%s)\n' % (loads,))
                                attrs.append('                {\n')
                                for z in range(size):
                                    attrs.append('                %s%s[%d] = %s.%s[%d];\n' % (pres, name, z, default, name, z))
                                attrs.append('                }\n')
                            else:
                                for z in range(size):
                                    attrs.append('            %s%s[%d] = %s.%s[%d];\n' % (pres, name, z, default, name, z))
                        else:
                            if loads:
                                attrs.append('            if(%s)\n' % (loads,))
                                attrs.append('                %s%s = %s.%s;\n' % (pres, name, default, name))
                            else:
                                attrs.append('            %s%s = %s.%s;\n' % (pres, name, default, name))
                        attrs.append('            return;\n')
                    elif 'Array' in t:
                        attrs.append(' //%s\n' % (name,))
                        attrs.append('            return UNKNOWN_FIELD;\n')
                    else:
                        attrs.append(' //%s\n' % (name,))
                        if loads:
                            attrs.append('            if(%s)\n' % (loads,))
                            attrs.append('                %s%s = %s.%s;\n' % (pres, name, default, name))
                        else:
                            attrs.append('            %s%s = %s.%s;\n' % (pres, name, default, name))
                        attrs.append('            return;\n')
                else:
                    print "111", name, type, size, ip, vars
        return attrs

    apiVars = []
    madeChanges = True
    apiVars = cl_vars
    attrVars = []
    while madeChanges:
        madeChanges = False
        attrVars = []
        caseNum = 7
        x = []
        usedNames = set()
        for attr in makeAttrApi(apiVars):
            if isinstance(attr, list):
                x += attr
            elif attr.startswith(' //'):
                inf = re_name.search(attr)
                if inf:
                    name = inf.groups()[0]
                    try:
                        num = int(name[-1])
                        tname = name[:-1]
                    except:
                        num = 10
                        tname = name
                    while name in usedNames:
                        name = tname + `num`
                        num += 1
                    usedNames.add(name)
                x.append('        case %d: //%s\n' % (caseNum,name))
                caseNum += 1
            else:
                x.append(attr)
        attrVars = x

        getVars = []
        caseNum = 7
        x = []
        usedNames = set()
        for attr in makeGetApi(apiVars):
            if isinstance(attr, list):
                x += attr
            elif attr.startswith(' //'):
                inf = re_name.search(attr)
                if inf:
                    name = inf.groups()[0]
                    try:
                        num = int(name[-1])
                        tname = name[:-1]
                    except:
                        num = 10
                        tname = name
                    while name in usedNames:
                        name = tname + `num`
                        num += 1
                    usedNames.add(name)
                x.append('        case %d: //%s\n' % (caseNum,name))
                caseNum += 1
            else:
                x.append(attr)
        getVars = x

        setVars = []
        caseNum = 7
        x = []
        usedNames = set()
        for attr in makeSetApi(apiVars):
            if isinstance(attr, list):
                x += attr
            elif attr.startswith(' //'):
                inf = re_name.search(attr)
                if inf:
                    name = inf.groups()[0]
                    try:
                        num = int(name[-1])
                        tname = name[:-1]
                    except:
                        num = 10
                        tname = name
                    while name in usedNames:
                        name = tname + `num`
                        num += 1
                    usedNames.add(name)
                x.append('        case %d: //%s\n' % (caseNum,name))
                caseNum += 1
            else:
                x.append(attr)
        setVars = x

        delVars = []
        caseNum = 7
        x = []
        usedNames = set()
        for attr in makeDelApi(apiVars):
            if isinstance(attr, list):
                x += attr
            elif attr.startswith(' //'):
                inf = re_name.search(attr)
                if inf:
                    name = inf.groups()[0]
                    try:
                        num = int(name[-1])
                        tname = name[:-1]
                    except:
                        num = 10
                        tname = name
                    while name in usedNames:
                        name = tname + `num`
                        num += 1
                    usedNames.add(name)
                x.append('        case %d: //%s\n' % (caseNum,name))
                caseNum += 1
            else:
                x.append(attr)
        delVars = x

    if True: #api generation
        f = open('%sAPI.cpp' % cltag, 'w')
        f.write('/*\nGPL License and Copyright Notice ============================================\n This file is part of CBash.\n\n CBash is free software; you can redistribute it and/or\n modify it under the terms of the GNU General Public License\n as published by the Free Software Foundation; either version 2\n of the License, or (at your option) any later version.\n\n CBash is distributed in the hope that it will be useful,\n but WITHOUT ANY WARRANTY; without even the implied warranty of\n MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n GNU General Public License for more details.\n\n You should have received a copy of the GNU General Public License\n along with CBash; if not, write to the Free Software Foundation,\n Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.\n\n CBash copyright (C) 2010 Waruddar\n=============================================================================\n*/\n#include "..\\..\\..\\Common.h"\n')
        f.write('#include "..\\%s.h"\n\n' % cltag)
        f.write('namespace FNV\n{\n')
        
        f.write('UINT32 %s::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)\n    {\n    switch(FieldID)\n        {\n        case 0: //recType\n            return GetType();\n        case 1: //flags1\n            return UINT32_FLAG_FIELD;\n        case 2: //fid\n            return FORMID_FIELD;\n        case 3: //versionControl1\n            switch(WhichAttribute)\n                {\n                case 0: //fieldType\n                    return UINT8_ARRAY_FIELD;\n                case 1: //fieldSize\n                    return 4;\n                default:\n                    return UNKNOWN_FIELD;\n                }\n            return UNKNOWN_FIELD;\n' % (cltag,))
        if ('EDID', 'StringRecord', 0, False, []) in cl_vars:
            f.write('        case 4: //eid\n            return ISTRING_FIELD;\n')
        else:
            f.write('        case 4: //eid\n            return MISSING_FIELD;\n')
        f.write('        case 5: //formVersion\n            return UINT16_FIELD;\n        case 6: //versionControl2\n            switch(WhichAttribute)\n                {\n                case 0: //fieldType\n                    return UINT8_ARRAY_FIELD;\n                case 1: //fieldSize\n                    return 2;\n                default:\n                    return UNKNOWN_FIELD;\n                }\n            return UNKNOWN_FIELD;\n')
        f.write(''.join(attrVars))
        f.write('        default:\n            return UNKNOWN_FIELD;\n        }\n    return UNKNOWN_FIELD;\n    }\n\nvoid * %s::GetField(FIELD_IDENTIFIERS, void **FieldValues)\n    {\n    switch(FieldID)\n        {\n        case 1: //flags1\n            return &flags;\n        case 2: //fid\n            return &formID;\n        case 3: //versionControl1\n            *FieldValues = &flagsUnk;\n            return NULL;\n' % (cltag,))
        if ('EDID', 'StringRecord', 0, False, []) in cl_vars:
            f.write('        case 4: //eid\n            return EDID.value;\n')
        f.write('        case 5: //formVersion\n            return &formVersion;\n        case 6: //versionControl2\n            *FieldValues = &versionControl2[0];\n            return NULL;\n')
        f.write(''.join(getVars))
        f.write('        default:\n            return NULL;\n        }\n    return NULL;\n    }\n\nbool %s::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)\n    {\n    switch(FieldID)\n        {\n        case 1: //flags1\n            SetHeaderFlagMask(*(UINT32 *)FieldValue);\n            break;\n        case 3: //versionControl1\n            if(ArraySize != 4)\n                break;\n            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8ARRAY)FieldValue)[0];\n            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8ARRAY)FieldValue)[1];\n            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8ARRAY)FieldValue)[2];\n            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8ARRAY)FieldValue)[3];\n            break;\n' % (cltag,))

        if ('EDID', 'StringRecord', 0, False, []) in cl_vars:
            f.write('        case 4: //eid\n            EDID.Copy((STRING)FieldValue);\n            break;\n')
        f.write('        case 5: //formVersion\n            formVersion = *(UINT16 *)FieldValue;\n            break;\n        case 6: //versionControl2\n            if(ArraySize != 2)\n                break;\n            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];\n            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];\n            break;\n')
        f.write(''.join(setVars))
        f.write('        default:\n            break;\n        }\n    return false;\n    }\n\nvoid %s::DeleteField(FIELD_IDENTIFIERS)\n    {\n    switch(FieldID)\n        {\n        case 1: //flags1\n            SetHeaderFlagMask(0);\n            return;\n        case 3: //versionControl1\n            flagsUnk = 0;\n            return;\n' % cltag)

        if ('EDID', 'StringRecord', 0, False, []) in cl_vars:
            f.write('        case 4: //eid\n            EDID.Unload();\n            return;\n')
        f.write('        case 5: //formVersion\n            formVersion = 0;\n            return;\n        case 6: //versionControl2\n            versionControl2[0] = 0;\n            versionControl2[1] = 0;\n            return;\n')

        f.write(''.join(delVars))
        f.write('        default:\n            return;\n        }\n    }\n}')
        f.close()
sys.exit(0)

f = open('funcs.txt','w')
for name, vars in str_vars.iteritems():
    funcs = str_funcs[name]
    for func in funcs:
        if func == name:
            struct = '%s::%s():\n' % (name, func)
            body = ''
            hadVars = False
            for _rec, type, n, s in vars:
                if s is None:
                    hadVars = True
                    if type == 'FLOAT32':
                        struct += '    %s(0.0f),\n' % (n,)
                    else:
                        struct += '    %s(0),\n' % (n,)
                else:
                    body += '    memset(&%s[0], 0x00, sizeof(%s));\n' % (n, n)
            if hadVars:
                struct = struct[:-2] + '\n'
                hadVars = False
            struct += '    {\n'
            struct += body if len(body) > 1 else '    //\n'
            struct += '    }\n\n'
        elif func == '~%s' % (name):
            struct = '%s::%s()\n    {\n    //\n    }\n\n' % (name, func)
        elif func == '==':
            struct = 'bool %s::operator ==(const %s &other) const\n    {\n    return (' % (name, name)
            hadVars = False
            v = []
            for _rec, type, n, s in vars:
                if 'unused' in n.lower():
                    continue
                if s is None:
                    if type == 'FLOAT32':
                        v += ['AlmostEqual(%s,other.%s,2)' % (n, n)]
                    else:
                        v += ['%s == other.%s' % (n, n)]
                else:
                    try:
                        size = int(s)
                    except ValueError:
                        try:
                            size = int(s, 16)
                        except:
                            raise
                    for x in range(size):
                        v += ['%s[%d] == other.%s[%d]' % (n, x, n, x)]
            struct += ' &&\n            '.join(v) + ');\n'
            struct += '    }\n\n'
        elif func == '!=':
            struct = 'bool %s::operator !=(const %s &other) const\n    {\n    return !(*this == other);\n    }\n\n' % (name, name)
        else:
            struct = 'XYXX %s::%s(XYXX)\n    {\n    //XYXX\n    }\n\n' % (name, func)
        f.write(struct)
f.close()
print str_vars
print
print str_funcs['GENSCR_']
sys.exit(0)
caseNum = caseStart
f.write('\n\n\n\n')
for tag, type, var in vars:
    if '[' in var:
        str = "        case %d: //%s\n            switch(WhichAttribute)\n                {\n                case 0: //fieldType\n                    return %s_ARRAY_FIELD;\n                case 1: //fieldSize\n                    return %s;\n                default:\n                    return UNKNOWN_FIELD;\n                }\n            return UNKNOWN_FIELD;\n" % (caseNum, var[:var.find('[')], type, var[var.find('[')+1:var.find(']')])
    else:
        str = '        case %d: //%s\n            return %s_FIELD;\n' % (caseNum, var, type)
    f.write(str)
    caseNum += 1

caseNum = caseStart
f.write('\n\n\n\n')
for tag, type, var in vars:
    if '[' in var:
        str = "        case %d: //%s\n            *FieldValues = &%s.value.%s[0];\n            return NULL;\n" % (caseNum, var[:var.find('[')], tag, var[:var.find('[')])
    else:
        str = "        case %d: //%s\n            return &%s.value.%s;\n" % (caseNum, var, tag, var)
    f.write(str)
    caseNum += 1

caseNum = caseStart
f.write('\n\n\n\n')
for tag, type, var in vars:
    if '[' in var:
        str = "        case %d: //%s\n            if(ArraySize != %s)\n                break;\n" % (caseNum, var[:var.find('[')], var[var.find('[')+1:var.find(']')])
        size = int(var[var.find('[')+1:var.find(']')])
        for x in range(size):
            str += "            %s[%d] = ((%sARRAY)FieldValue)[%d];\n" % (var[:var.find('[')], x, type, x)
        str += "            break;\n"
    elif type == 'FORMID':
        str = "        case %d: //%s\n            %s.value.%s = *(%s *)FieldValue;\n            return true;\n" % (caseNum, var, tag, var, type)
    else:
        str = "        case %d: //%s\n            %s.value.%s = *(%s *)FieldValue;\n            break;\n" % (caseNum, var, tag, var, type)
    f.write(str)
    caseNum += 1

caseNum = caseStart
f.write('\n\n\n\n')
for tag, type, var in vars:
    if '[' in var:
        str = "        case %d: //%s\n" % (caseNum, var[:var.find('[')])
        size = int(var[var.find('[')+1:var.find(']')])
        for x in range(size):
            str += "            %s[%d] = default%s.%s[%d];\n" % (var[:var.find('[')], x, tag, var[:var.find('[')], x)
        str += "            return;\n"
    else:
        str = "        case %d: //%s\n            %s.value.%s = default%s.%s;\n            return;\n" % (caseNum, var, tag, var, tag, var)
    f.write(str)
    caseNum += 1
f.close()