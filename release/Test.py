from CBashInterface import *

def TestMinimalLoad():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    Current.minimalLoad(LoadMasters=True)

def TestFullLoad():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    Current.fullLoad(LoadMasters=True)
    
def TestReadWriteAll():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestALL.esp", True)
    ##Preloading seems to have almost no effect (~2ms on all simple, CopyAsNew) on speed when later reading...
    ##Not preloading would make it faster if not all records being iterated, and save memory...

    Current.fullLoad(LoadMasters=True)

    for record in Current[0].GMST:
        record.CopyAsOverride(newMod)
    for record in Current[0].GLOB:
        record.CopyAsNew(newMod)
        record.CopyAsOverride(newMod)
    for record in Current[0].CLAS:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].FACT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].HAIR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].EYES:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].RACE:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].SOUN:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].SKIL:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].MGEF:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].SCPT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].LTEX:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].ENCH:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].SPEL:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].BSGN:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].ACTI:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].APPA:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].ARMO:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].BOOK:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].CLOT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].CONT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].DOOR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].INGR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].LIGH:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].MISC:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].STAT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].GRAS:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].TREE:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].FLOR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].FURN:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].WEAP:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].AMMO:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].NPC_:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].CREA:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].LVLC:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].SLGM:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].KEYM:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].ALCH:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].SBSP:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].SGST:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].LVLI:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].WTHR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].CLMT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].REGN:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
##    for record in Current[0].CELL:
##        trgCell = record.CopyAsOverride(newMod)
##        for npcRef in record.ACHR:
##            npcRef.CopyAsOverride(trgCell)
##        for creaRef in record.ACRE:
##            creaRef.CopyAsOverride(trgCell)
##        for objRef in record.REFR:
##            objRef.CopyAsOverride(trgCell)
##        Pgrd = record.PGRD
##        if(Pgrd): Pgrd.CopyAsOverride(trgCell)
##        
##        trgCell = record.CopyAsNew(newMod)
##        for npcRef in record.ACHR:
##            npcRef.CopyAsNew(trgCell)
##        for creaRef in record.ACRE:
##            creaRef.CopyAsNew(trgCell)
##        for objRef in record.REFR:
##            objRef.CopyAsNew(trgCell)
##        Pgrd = record.PGRD
##        if(Pgrd): Pgrd.CopyAsNew(trgCell)
##
##        
##    for record in Current[0].WRLD:
##        trgWrld = record.CopyAsOverride(newMod)
##        road = record.ROAD
##        if(road != None): road.CopyAsOverride(trgWrld)
##        for wrldCell in record.CELLS:
##            trgCell = wrldCell.CopyAsOverride(trgWrld)
##            cLand = wrldCell.LAND
##            if(cLand):
##                cLand.CopyAsOverride(trgCell)
##            for npcRef in wrldCell.ACHR:
##                npcRef.CopyAsOverride(trgCell)
##            for creaRef in wrldCell.ACRE:
##                creaRef.CopyAsOverride(trgCell)
##            for objRef in wrldCell.REFR:
##                objRef.CopyAsOverride(trgCell)
##            Pgrd = wrldCell.PGRD
##            if(Pgrd): Pgrd.CopyAsOverride(trgCell)
##            
##        trgWrld = record.CopyAsNew(newMod)
##        road = record.ROAD
##        if(road != None): road.CopyAsNew(trgWrld)
##        for wrldCell in record.CELLS:
##            trgCell = wrldCell.CopyAsNew(trgWrld)
##            cLand = wrldCell.LAND
##            if(cLand):
##                cLand.CopyAsNew(trgCell)
##            for npcRef in wrldCell.ACHR:
##                npcRef.CopyAsNew(trgCell)
##            for creaRef in wrldCell.ACRE:
##                creaRef.CopyAsNew(trgCell)
##            for objRef in wrldCell.REFR:
##                objRef.CopyAsNew(trgCell)
##            Pgrd = wrldCell.PGRD
##            if(Pgrd): Pgrd.CopyAsNew(trgCell)
##            
##    for record in Current[0].DIAL:
##        newOver = record.CopyAsOverride(newMod)
##        newNew = record.CopyAsNew(newMod)
##        for info in record.INFO:
##            info.CopyAsOverride(newOver)
##            info.CopyAsNew(newNew)
    for record in Current[0].QUST:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].IDLE:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].PACK:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].CSTY:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].LSCR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].LVSP:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].ANIO:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].WATR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
    for record in Current[0].EFSH:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)

    print "ALL:Save Test - TestALL.esp"
    newMod.safeSave()
    print "ALL:Finished testing"
def TestTES4():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestTES4.esp", True)
    Current.minimalLoad(LoadMasters=True)
    print "TES4:Read Test"
    for record in Current.TES4:
        print
        print "ModName    :", record._ModName
        print "flags1     :", record.flags1
        print "flags2     :", record.flags2
        print "version    :", record.version
        print "numRecords :", record.numRecords
        print "nextObject : %06X" % record.nextObject
        print "ofst_p     :", record.ofst_p
        print "dele_p     :", record.dele_p
        print "author     :", record.author
        print "description:", record.description
        print "masters    :", record.masters
        break
    print "TES4:Set Test"
    print "version..."
    newMod.TES4.version = Current[0].TES4.version
    print "numRecords..."
    newMod.TES4.numRecords = Current[0].TES4.numRecords
    print "nextObject..."
    newMod.TES4.nextObject = Current[0].TES4.nextObject
    print "ofst_p..."
    newMod.TES4.ofst_p = Current[0].TES4.ofst_p
    print "dele_p..."
    newMod.TES4.dele_p = Current[0].TES4.dele_p
    print "author..."
    newMod.TES4.author = Current[0].TES4.author
    print "description..."
    newMod.TES4.description = Current[0].TES4.description
    print "masters..."
##    newMod.TES4.masters = Current[0].TES4.masters
    newMod.TES4.masters = ["Oblivion.esm"]
    print "TES4:Set Test Results"
    print "ModName   :", newMod.TES4._ModName
    print "flags1     :", newMod.TES4.flags1
    print "flags2     :", newMod.TES4.flags2
    print "version    :", newMod.TES4.version
    print "numRecords :", newMod.TES4.numRecords
    print "nextObject : %06X" % newMod.TES4.nextObject
    print "ofst_p     :", newMod.TES4.ofst_p
    print "dele_p     :", newMod.TES4.dele_p
    print "author     :", newMod.TES4.author
    print "description:", newMod.TES4.description
    print "masters    :", newMod.TES4.masters    

    print "TES4:Save Test - TestTES4.esp"
    newMod.safeSave()
    print "TES4:Finished testing"

def TestGMST():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestGMST.esp", True)
    Current.minimalLoad(LoadMasters=True)
    print "GMST:Read Test"
    for record in Current.GMST:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        print "value  :", record.value
        break
    print "GMST:Create Record Test"
    newRecord = newMod.createGMSTRecord("sWarString")
    print "GMST:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "value..."
    newRecord.value = "It works!"
    print "GMST:Set Test Results"
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "value  :", newRecord.value
    print "GMST:CopyAsOverride Test"
    for record in Current[0].GMST:
        record.CopyAsOverride(newMod)
    print "GMST:Save Test - TestGMST.esp"
    newMod.safeSave()
    print "GMST:Finished testing"

def TestGLOB():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestGLOB.esp", True)
    Current.minimalLoad(LoadMasters=True)
    print "GLOB:Read Test"
    for record in Current.GLOB:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        print "format :", record.format
        print "value  :", record.value
        break

    print "GLOB:Create Record Test"
    newRecord = newMod.createGLOBRecord()
    print "GLOB:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WarGlobalTest"
    print "format..."
    newRecord.format = 'f'
    print "value..."
    newRecord.value = 12.2
    print "GLOB:Set Test Results"
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "format :", newRecord.format
    print "value  :", newRecord.value
    print "GLOB:CopyAsOverride Test"
    for record in Current[0].GLOB:
        record.CopyAsOverride(newMod)
    print "GLOB:CopyAsNew Test"
    for record in Current[0].GLOB:
        record.CopyAsNew(newMod)
    print "GLOB:Save Test - TestGLOB.esp"
    newMod.safeSave()
    print "GLOB:Finished testing"

def TestCLAS():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCLAS.esp", True)
    Current.minimalLoad(LoadMasters=True)
    print "CLAS:Read Test"
    for record in Current.CLAS:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        
        print "full          :", record.full
        print "description   :", record.description
        print "iconPath      :", record.iconPath
        print "primary1      :", record.primary1
        print "primary2      :", record.primary2
        print "specialization:", record.specialization
        print "major1        :", record.major1
        print "major2        :", record.major2
        print "major3        :", record.major3
        print "major4        :", record.major4
        print "major5        :", record.major5
        print "major6        :", record.major6
        print "major7        :", record.major7
        print "flags         :", record.flags
        print "services      :", record.services
        print "trainSkill    :", record.trainSkill
        print "trainLevel    :", record.trainLevel
        print "unused1       :", record.unused1
        break

    print "CLAS:Create Record Test"
    newRecord = newMod.createCLASRecord()
    print "CLAS:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WarCLASTest"
    
    print "full..."
    newRecord.full = "Waruddar! RARGH!"
    print "description..."
    newRecord.description = "This is just a very long and quick test of a string that is absolutely pointless for the vast majority of cases.!!!"
    print "iconPath..."
    newRecord.iconPath = r"ICON\asdf.ico"
    print "primary1..."
    newRecord.primary1 = 8
    print "primary2..."
    newRecord.primary2 = 9
    print "specialization..."
    newRecord.specialization = 1
    print "major1..."
    newRecord.major1 = 1
    print "major2..."
    newRecord.major2 = 2
    print "major3..."
    newRecord.major3 = 3
    print "major4..."
    newRecord.major4 = 4
    print "major5..."
    newRecord.major5 = 5
    print "major6..."
    newRecord.major6 = 6
    print "major7..."
    newRecord.major7 = 7
    print "flags...."
    newRecord.flags = 0x07
    print "services..."
    newRecord.services = 0x08
    print "trainSkill..."
    newRecord.trainSkill = 13
    print "trainLevel..."
    newRecord.trainLevel = 60
    print "unused1..."
    newRecord.unused1 = [0x01, 0xFF]
        
    print "CLAS:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "full          :", newRecord.full
    print "description   :", newRecord.description
    print "iconPath      :", newRecord.iconPath
    print "primary1      :", newRecord.primary1
    print "primary2      :", newRecord.primary2
    print "specialization:", newRecord.specialization
    print "major1        :", newRecord.major1
    print "major2        :", newRecord.major2
    print "major3        :", newRecord.major3
    print "major4        :", newRecord.major4
    print "major5        :", newRecord.major5
    print "major6        :", newRecord.major6
    print "major7        :", newRecord.major7
    print "flags         :", newRecord.flags
    print "services      :", newRecord.services
    print "trainSkill    :", newRecord.trainSkill
    print "trainLevel    :", newRecord.trainLevel
    print "unused1       :", newRecord.unused1
    print "CLAS:CopyAsOverride Test"
    for record in Current[0].CLAS:
        record.CopyAsOverride(newMod)
    print "CLAS:CopyAsNew Test"
    for record in Current[0].CLAS:
        record.CopyAsNew(newMod)
    print "CLAS:Save Test - TestCLAS.esp"
    newMod.safeSave()
    print "CLAS:Finished testing"


def TestFACT():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestFACT.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.FACT:
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        
        print "full                :", record.full
        print "relations           :"
        for relation in record.relations:
            print "  %i: Faction: %08X, Mod: %i" % (relation._listIndex, relation.faction, relation.mod)

        print "flags               :", record.flags
        print "crimeGoldMultiplier :", record.crimeGoldMultiplier
        print "ranks               :"
        for rank in record.ranks:
            print "  rank: %i\n    male:%s\n    female:%s\n    insigniaPath:%s" % (rank.rank, rank.male, rank.female, rank.insigniaPath)
        print
        break

    print "FACT:Create Record Test"
    newRecord = newMod.createFACTRecord()
    print "FACT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "FACTWarTest"
    print "full..."
    newRecord.full = "Waruddar's Faction"
    print "relations..."
    newRelation = newRecord.newRelationsElement()
    newRelation.faction = 1
    newRelation.mod = -69
    newRelation = newRecord.newRelationsElement()
    newRelation.faction = 2
    newRelation.mod = 67
    newRelation = newRecord.newRelationsElement()
    newRelation.faction = 15
    newRelation.mod = 100
    print "flags..."
    newRecord.flags = 15
    print "crimeGoldMultiplier..."
    newRecord.crimeGoldMultiplier = 1.5
    print "ranks..."
    newRank = newRecord.newRanksElement()
    newRank.rank = 0
    newRank.male = "HELP ME"
    newRank.female = "LOST MY MIND"
    newRank.insigniaPath = "WHERE is IT?"
    newRank = newRecord.newRanksElement()
    newRank.rank = 1
    newRank.male = "Is it here?"
    newRank.female = "Or, there?"
    newRank.insigniaPath = "Where?"
    newRank = newRecord.newRanksElement()
    newRank.rank = 2
    newRank.male = "Silly me"
    newRank.female = "Here it is"
    newRank.insigniaPath = "Found it"

    print "FACT:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid    
    print "full               :", newRecord.full    
    print "relations          :"
    for relation in newRecord.relations:
        print "  %i: Faction: %08X, Mod: %i" % (relation._listIndex, relation.faction, relation.mod)
    print "flags              :", newRecord.flags    
    print "crimeGoldMultiplier:", newRecord.crimeGoldMultiplier
    print "ranks              :"
    for rank in newRecord.ranks:
        print "  rank: %i\n    male:%s\n    female:%s\n    insigniaPath:%s" % (rank.rank, rank.male, rank.female, rank.insigniaPath)

    print "FACT:CopyAsOverride Test"
    for record in Current[0].FACT:
        record.CopyAsOverride(newMod)

    print "FACT:CopyAsNew Test"
    for record in Current[0].FACT:
        record.CopyAsNew(newMod)

    print "FACT:Save Test - TestFACT.esp"
    newMod.safeSave()
    print "FACT:Finished testing"

def TestHAIR():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestHAIR.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.HAIR:
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        
        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "iconPath:", record.iconPath
        print "flags   :", record.flags
        print
        break



    print "HAIR:Create Record Test"
    newRecord = newMod.createHAIRRecord()
    print "HAIR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "HAIRWarTest"
    print "full..."
    newRecord.full = "Fancy HAIR"

    print "modPath..."
    newRecord.modPath = r"Blah\hay\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "iconPath..."
    newRecord.iconPath = r"hair\path\test.dds"
    
    print "flags..."
    newRecord.flags = 15


    print "HAIR:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid    
    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath:", newRecord.iconPath
    print "flags   :", newRecord.flags

    print "HAIR:CopyAsOverride Test"
    for record in Current[0].HAIR:
        record.CopyAsOverride(newMod)

    print "HAIR:CopyAsNew Test"
    for record in Current[0].HAIR:
        record.CopyAsNew(newMod)

    print "HAIR:Save Test - TestHAIR.esp"
    newMod.safeSave()
    print "HAIR:Finished testing"

def TestEYES():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestEYES.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.EYES:
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        
        print "full    :", record.full
        print "iconPath:", record.iconPath
        print "flags   :", record.flags
        print
        break



    print "EYES:Create Record Test"
    newRecord = newMod.createEYESRecord()
    print "EYES:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "EYESWarTest"
    print "full..."
    newRecord.full = "Fancy EYES"    
    print "iconPath..."
    newRecord.iconPath = r"EYES\p\nath\test.dds"    
    print "flags..."
    newRecord.flags = 15

    print "EYES:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid    
    print "full    :", newRecord.full
    print "iconPath:", newRecord.iconPath
    print "flags   :", newRecord.flags

    print "EYES:CopyAsOverride Test"
    for record in Current[0].EYES:
        record.CopyAsOverride(newMod)

    print "EYES:CopyAsNew Test"
    for record in Current[0].EYES:
        record.CopyAsNew(newMod)

    print "EYES:Save Test - TestEYES.esp"
    newMod.safeSave()
    print "EYES:Finished testing"

def TestRACE():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestRACE.esp", True)
    Current.minimalLoad(LoadMasters=True)
    for record in Current.RACE:
        print
        print "fid    : %08X" % record.fid
        print "flags1 :", record.flags1
        print "flags2 :", record.flags2
        print "eid    :", record.eid
        
        print "full      :", record.full
        print "text      :", record.text
        print "spells    :"
        for spell in record.spells:
            print "  %08X" % spell
            
        print "relations :"
        for relation in record.relations:
            print "  %i: Faction: %08X, Mod: %i" % (relation._listIndex, relation.faction, relation.mod)
        
        print "  skill1:", record.skill1, ", boost:", record.skill1Boost
        print "  skill2:", record.skill2, ", boost:", record.skill2Boost
        print "  skill3:", record.skill3, ", boost:", record.skill3Boost
        print "  skill4:", record.skill4, ", boost:", record.skill4Boost
        print "  skill5:", record.skill5, ", boost:", record.skill5Boost
        print "  skill6:", record.skill6, ", boost:", record.skill6Boost
        print "  skill7:", record.skill7, ", boost:", record.skill7Boost

        print "unused1          :", record.unused1
        
        print "maleHeight       :", record.maleHeight
        print "femaleHeight     :", record.femaleHeight
        print "maleWeight       :", record.maleWeight
        print "femaleWeight     :", record.femaleWeight
        print "flags            :", record.flags
        
        print "maleVoice        :", record.maleVoice
        print "femaleVoice      :", record.femaleVoice
        
        print "defaultHairMale  :", record.defaultHairMale
        print "defaultHairFemale:", record.defaultHairFemale
        print "defaultHairColor :", record.defaultHairColor

        print "mainClamp        :", record.mainClamp
        print "faceClamp        :", record.faceClamp

        print "maleStrength     :", record.maleStrength
        print "maleIntelligence :", record.maleIntelligence
        print "maleWillpower    :", record.maleWillpower
        print "maleAgility      :", record.maleAgility
        print "maleSpeed        :", record.maleSpeed
        print "maleEndurance    :", record.maleEndurance
        print "malePersonality  :", record.malePersonality
        print "maleLuck         :", record.maleLuck

        print "femaleStrength     :", record.femaleStrength
        print "femaleIntelligence :", record.femaleIntelligence
        print "femaleWillpower    :", record.femaleWillpower
        print "femaleAgility      :", record.femaleAgility
        print "femaleSpeed        :", record.femaleSpeed
        print "femaleEndurance    :", record.femaleEndurance
        print "femalePersonality  :", record.femalePersonality
        print "femaleLuck         :", record.femaleLuck

        print "head.modPath       :", record.head.modPath
        print "head.modb          :", record.head.modb
        print "head.iconPath      :", record.head.iconPath
        print "head.modt_p        :", record.head.modt_p

        print "maleEars.modPath   :", record.maleEars.modPath
        print "maleEars.modb      :", record.maleEars.modb
        print "maleEars.iconPath  :", record.maleEars.iconPath
        print "maleEars.modt_p    :", record.maleEars.modt_p

        print "femaleEars.modPath :", record.femaleEars.modPath
        print "femaleEars.modb    :", record.femaleEars.modb
        print "femaleEars.iconPath:", record.femaleEars.iconPath
        print "femaleEars.modt_p  :", record.femaleEars.modt_p

        print "mouth.modPath      :", record.mouth.modPath
        print "mouth.modb         :", record.mouth.modb
        print "mouth.iconPath     :", record.mouth.iconPath
        print "mouth.modt_p       :", record.mouth.modt_p

        print "teethLower.modPath :", record.teethLower.modPath
        print "teethLower.modb    :", record.teethLower.modb
        print "teethLower.iconPath:", record.teethLower.iconPath
        print "teethLower.modt_p  :", record.teethLower.modt_p

        print "teethUpper.modPath :", record.teethUpper.modPath
        print "teethUpper.modb    :", record.teethUpper.modb
        print "teethUpper.iconPath:", record.teethUpper.iconPath
        print "teethUpper.modt_p  :", record.teethUpper.modt_p

        print "tongue.modPath     :", record.tongue.modPath
        print "tongue.modb        :", record.tongue.modb
        print "tongue.iconPath    :", record.tongue.iconPath
        print "tongue.modt_p      :", record.tongue.modt_p

        print "leftEye.modPath    :", record.leftEye.modPath
        print "leftEye.modb       :", record.leftEye.modb
        print "leftEye.iconPath   :", record.leftEye.iconPath
        print "leftEye.modt_p     :", record.leftEye.modt_p

        print "rightEye.modPath   :", record.rightEye.modPath
        print "rightEye.modb      :", record.rightEye.modb
        print "rightEye.iconPath  :", record.rightEye.iconPath
        print "rightEye.modt_p    :", record.rightEye.modt_p

        print "maleTailModel.modPath :", record.maleTailModel.modPath
        print "maleTailModel.modb    :", record.maleTailModel.modb
        print "maleTailModel.modt_p  :", record.maleTailModel.modt_p        

        print "maleUpperBodyPath     :", record.maleUpperBodyPath
        print "maleLowerBodyPath     :", record.maleLowerBodyPath
        print "maleHandPath          :", record.maleHandPath
        print "maleFootPath          :", record.maleFootPath
        print "maleTailPath          :", record.maleTailPath
        
        print "femaleTailModel.modPath :", record.femaleTailModel.modPath
        print "femaleTailModel.modb    :", record.femaleTailModel.modb
        print "femaleTailModel.modt_p  :", record.femaleTailModel.modt_p

        print "femaleUpperBodyPath     :", record.femaleUpperBodyPath
        print "femaleLowerBodyPath     :", record.femaleLowerBodyPath
        print "femaleHandPath          :", record.femaleHandPath
        print "femaleFootPath          :", record.femaleFootPath
        print "femaleTailPath          :", record.femaleTailPath

        print "hairs :"
        for hair in record.hairs:
            print "  %08X" % hair

        print "eyes :"
        for eye in record.eyes:
            print "  %08X" % eye

        print "fggs_p:", record.fggs_p   
        print "fgga_p:", record.fgga_p 
        print "fgts_p:", record.fgts_p
        
        print "snam:", record.snam
        break
        
    print "RACE:Create Record Test"
    newRecord = newMod.createRACERecord()
    print "RACE:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "RACEWarTest"
    print "full..."
    newRecord.full = "Fancy RACE"

    newRecord.text = "BLAH BLAH BLHARGH"
    newRecord.spells = [0xFF000121, 0xFE000222]
    newRelation = newRecord.newRelationsElement()
    newRelation.faction = 0x00000800
    newRelation.mod = 100
    newRelation = newRecord.newRelationsElement()
    newRelation.faction = 0x00000801    
    newRelation.mod = 50
    newRelation = newRecord.newRelationsElement()
    newRelation.faction = 0x00000802    
    newRelation.mod = 60
    newRelation = newRecord.newRelationsElement()
    newRelation.faction = 0x00000803    
    newRelation.mod = 70
    nRelations = newRecord.relations
    newRecord.relations = [nRelations[1],nRelations[0],nRelations[2],nRelations[3]]

    newRecord.skill1 = 1
    newRecord.skill1Boost = 11
    newRecord.skill2 = 2
    newRecord.skill2Boost = 12
    newRecord.skill3 = 3
    newRecord.skill3Boost = 13
    newRecord.skill4 = 4
    newRecord.skill4Boost = 14
    newRecord.skill5 = 5
    newRecord.skill5Boost = 15
    newRecord.skill6 = 6
    newRecord.skill6Boost = 16
    newRecord.skill7 = 7
    newRecord.skill7Boost = 17

    newRecord.unused1 = [0x00, 0xFF]

    newRecord.maleHeight = 1.5
    newRecord.femaleHeight = 1.6
    newRecord.maleWeight = 2.1
    newRecord.femaleWeight = 2.2


    newRecord.flags = 0x00000010

    newRecord.maleVoice = 0x00000011
    newRecord.femaleVoice = 0x00000012

    newRecord.defaultHairMale = 0x00000013
    newRecord.defaultHairFemale = 0x00000014
    newRecord.defaultHairColor = 1

    newRecord.mainClamp = 10.1
    newRecord.faceClamp = 1.2

    newRecord.maleStrength = 25
    newRecord.maleIntelligence = 26
    newRecord.maleWillpower = 27
    newRecord.maleAgility = 28
    newRecord.maleSpeed = 29
    newRecord.maleEndurance = 30
    newRecord.malePersonality = 31
    newRecord.maleLuck = 32

    newRecord.femaleStrength = 51
    newRecord.femaleIntelligence = 52
    newRecord.femaleWillpower = 53
    newRecord.femaleAgility = 54
    newRecord.femaleSpeed = 55
    newRecord.femaleEndurance = 56
    newRecord.femalePersonality = 57
    newRecord.femaleLuck = 58

    newRecord.head.modPath = r"asdf"
    newRecord.head.modb = 1.3
    newRecord.head.iconPath = r"fqeasdf"
    newRecord.head.modt_p = [0x01, 0x20]

    newRecord.maleEars.modPath = "maleEars"
    newRecord.maleEars.modb = 1.4
    newRecord.maleEars.iconPath = "maleEarsP"
    newRecord.maleEars.modt_p = [0x01, 0x20]

    newRecord.femaleEars.modPath = "femaleEars"
    newRecord.femaleEars.modb = 1.5
    newRecord.femaleEars.iconPath = "femaleEarsP"
    newRecord.femaleEars.modt_p = [0x01, 0x20]

    newRecord.mouth.modPath = "mouth"
    newRecord.mouth.modb = 1.6
    newRecord.mouth.iconPath = "mouthP"
    newRecord.mouth.modt_p = [0x01, 0x20]

    newRecord.teethLower.modPath = "teethLower"
    newRecord.teethLower.modb = 1.7
    newRecord.teethLower.iconPath = "teethLowerP"
    newRecord.teethLower.modt_p = [0x01, 0x20]

    newRecord.teethUpper.modPath = "teethUpper"
    newRecord.teethUpper.modb = 1.8
    newRecord.teethUpper.iconPath = "teethUpperP"
    newRecord.teethUpper.modt_p = [0x01, 0x20]

    newRecord.tongue.modPath = "tongue"
    newRecord.tongue.modb = 1.9
    newRecord.tongue.iconPath = "tongue"
    newRecord.tongue.modt_p = [0x01, 0x20]

    newRecord.leftEye.modPath = "leftEye"
    newRecord.leftEye.modb = 2.0
    newRecord.leftEye.iconPath = "leftEye"
    newRecord.leftEye.modt_p = [0x01, 0x20]

    newRecord.rightEye.modPath = "rightEye"
    newRecord.rightEye.modb = 2.1
    newRecord.rightEye.iconPath = "rightEye"
    newRecord.rightEye.modt_p = [0x01, 0x20]

    newRecord.maleTailModel.modPath = "maleTailModel"
    newRecord.maleTailModel.modb = 2.2
    newRecord.maleTailModel.modt_p = [0x01, 0x20]     

    newRecord.maleUpperBodyPath = "maleUpperBodyPath"
    newRecord.maleLowerBodyPath = "maleLowerBodyPath"
    newRecord.maleHandPath = "maleHandPath"
    newRecord.maleFootPath = "maleFootPath"
    newRecord.maleTailPath = "maleTailPath"

    newRecord.femaleTailModel.modPath = "femaleTailModel"
    newRecord.femaleTailModel.modb = 2.3
    newRecord.femaleTailModel.modt_p = [0x01, 0x20]

    newRecord.femaleUpperBodyPath = ""
    newRecord.femaleLowerBodyPath = "femaleLowerBodyPath"
    newRecord.femaleHandPath = "femaleHandPath"
    newRecord.femaleFootPath = "femaleFootPath"
    newRecord.femaleTailPath = "femaleTailPath"
    newRecord.hairs = [0x00000001, 0x01000002]
    newRecord.eyes = [0x00000003, 0x01000004]

    newRecord.fggs_p = [0x01, 0x20] 
    newRecord.fgga_p = [0x01, 0x20]
    newRecord.fgts_p = [0x01, 0x20]
    
    newRecord.snam = [0x01, 0x20]
    
    print "RACE:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "full      :", newRecord.full
    print "text      :", newRecord.text
    print "spells    :"
    for spell in newRecord.spells:
        print "  %08X" % spell
        
    print "relations :"
    for relation in newRecord.relations:
        print "  %i: Faction: %08X, Mod: %i" % (relation._listIndex, relation.faction, relation.mod)
    
    print "  skill1:", newRecord.skill1, ", boost:", newRecord.skill1Boost
    print "  skill2:", newRecord.skill2, ", boost:", newRecord.skill2Boost
    print "  skill3:", newRecord.skill3, ", boost:", newRecord.skill3Boost
    print "  skill4:", newRecord.skill4, ", boost:", newRecord.skill4Boost
    print "  skill5:", newRecord.skill5, ", boost:", newRecord.skill5Boost
    print "  skill6:", newRecord.skill6, ", boost:", newRecord.skill6Boost
    print "  skill7:", newRecord.skill7, ", boost:", newRecord.skill7Boost

    print "unused1          :", newRecord.unused1
    
    print "maleHeight       :", newRecord.maleHeight
    print "femaleHeight     :", newRecord.femaleHeight
    print "maleWeight       :", newRecord.maleWeight
    print "femaleWeight     :", newRecord.femaleWeight
    print "flags            :", newRecord.flags
    
    print "maleVoice        :", newRecord.maleVoice
    print "femaleVoice      :", newRecord.femaleVoice
    
    print "defaultHairMale  :", newRecord.defaultHairMale
    print "defaultHairFemale:", newRecord.defaultHairFemale
    print "defaultHairColor :", newRecord.defaultHairColor

    print "mainClamp        :", newRecord.mainClamp
    print "faceClamp        :", newRecord.faceClamp

    print "maleStrength     :", newRecord.maleStrength
    print "maleIntelligence :", newRecord.maleIntelligence
    print "maleWillpower    :", newRecord.maleWillpower
    print "maleAgility      :", newRecord.maleAgility
    print "maleSpeed        :", newRecord.maleSpeed
    print "maleEndurance    :", newRecord.maleEndurance
    print "malePersonality  :", newRecord.malePersonality
    print "maleLuck         :", newRecord.maleLuck

    print "femaleStrength     :", newRecord.femaleStrength
    print "femaleIntelligence :", newRecord.femaleIntelligence
    print "femaleWillpower    :", newRecord.femaleWillpower
    print "femaleAgility      :", newRecord.femaleAgility
    print "femaleSpeed        :", newRecord.femaleSpeed
    print "femaleEndurance    :", newRecord.femaleEndurance
    print "femalePersonality  :", newRecord.femalePersonality
    print "femaleLuck         :", newRecord.femaleLuck

    print "head.modPath       :", newRecord.head.modPath
    print "head.modb          :", newRecord.head.modb
    print "head.iconPath      :", newRecord.head.iconPath
    print "head.modt_p        :", newRecord.head.modt_p

    print "maleEars.modPath   :", newRecord.maleEars.modPath
    print "maleEars.modb      :", newRecord.maleEars.modb
    print "maleEars.iconPath  :", newRecord.maleEars.iconPath
    print "maleEars.modt_p    :", newRecord.maleEars.modt_p

    print "femaleEars.modPath :", newRecord.femaleEars.modPath
    print "femaleEars.modb    :", newRecord.femaleEars.modb
    print "femaleEars.iconPath:", newRecord.femaleEars.iconPath
    print "femaleEars.modt_p  :", newRecord.femaleEars.modt_p

    print "mouth.modPath      :", newRecord.mouth.modPath
    print "mouth.modb         :", newRecord.mouth.modb
    print "mouth.iconPath     :", newRecord.mouth.iconPath
    print "mouth.modt_p       :", newRecord.mouth.modt_p

    print "teethLower.modPath :", newRecord.teethLower.modPath
    print "teethLower.modb    :", newRecord.teethLower.modb
    print "teethLower.iconPath:", newRecord.teethLower.iconPath
    print "teethLower.modt_p  :", newRecord.teethLower.modt_p

    print "teethUpper.modPath :", newRecord.teethUpper.modPath
    print "teethUpper.modb    :", newRecord.teethUpper.modb
    print "teethUpper.iconPath:", newRecord.teethUpper.iconPath
    print "teethUpper.modt_p  :", newRecord.teethUpper.modt_p

    print "tongue.modPath     :", newRecord.tongue.modPath
    print "tongue.modb        :", newRecord.tongue.modb
    print "tongue.iconPath    :", newRecord.tongue.iconPath
    print "tongue.modt_p      :", newRecord.tongue.modt_p

    print "leftEye.modPath    :", newRecord.leftEye.modPath
    print "leftEye.modb       :", newRecord.leftEye.modb
    print "leftEye.iconPath   :", newRecord.leftEye.iconPath
    print "leftEye.modt_p     :", newRecord.leftEye.modt_p

    print "rightEye.modPath   :", newRecord.rightEye.modPath
    print "rightEye.modb      :", newRecord.rightEye.modb
    print "rightEye.iconPath  :", newRecord.rightEye.iconPath
    print "rightEye.modt_p    :", newRecord.rightEye.modt_p

    print "maleTailModel.modPath :", newRecord.maleTailModel.modPath
    print "maleTailModel.modb    :", newRecord.maleTailModel.modb
    print "maleTailModel.modt_p  :", newRecord.maleTailModel.modt_p        

    print "maleUpperBodyPath     :", newRecord.maleUpperBodyPath
    print "maleLowerBodyPath     :", newRecord.maleLowerBodyPath
    print "maleHandPath          :", newRecord.maleHandPath
    print "maleFootPath          :", newRecord.maleFootPath
    print "maleTailPath          :", newRecord.maleTailPath
    
    print "femaleTailModel.modPath :", newRecord.femaleTailModel.modPath
    print "femaleTailModel.modb    :", newRecord.femaleTailModel.modb
    print "femaleTailModel.modt_p  :", newRecord.femaleTailModel.modt_p

    print "femaleUpperBodyPath     :", newRecord.femaleUpperBodyPath
    print "femaleLowerBodyPath     :", newRecord.femaleLowerBodyPath
    print "femaleHandPath          :", newRecord.femaleHandPath
    print "femaleFootPath          :", newRecord.femaleFootPath
    print "femaleTailPath          :", newRecord.femaleTailPath

    print "hairs :"
    for hair in newRecord.hairs:
        print "  %08X" % hair

    print "eyes :"
    for eye in newRecord.eyes:
        print "  %08X" % eye

    print "fggs_p:", newRecord.fggs_p   
    print "fgga_p:", newRecord.fgga_p 
    print "fgts_p:", newRecord.fgts_p
    
    print "snam:", newRecord.snam

    print "RACE:CopyAsOverride Test"
    for record in Current[0].RACE:
        record.CopyAsOverride(newMod)

    print "RACE:CopyAsNew Test"
    for record in Current[0].RACE:
        record.CopyAsNew(newMod)

    print "RACE:Save Test - TestRACE.esp"
    newMod.safeSave()
    print "RACE:Finished testing"


def TestSOUN():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSOUN.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.SOUN:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        
        print "soundFile      :", record.soundFile
        print "minDistance    :", record.minDistance
        print "maxDistance    :", record.maxDistance
        print "freqAdjustment :", record.freqAdjustment
        print "unused1        :", record.unused1
        print "flags          :", record.flags
        print "unused2        :", record.unused2
        print "staticAtten    :", record.staticAtten
        print "stopTime       :", record.stopTime
        print "startTime      :", record.startTime
        break

    print "SOUN:Create Record Test"
    newRecord = newMod.createSOUNRecord()
    print "SOUN:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SOUNWarTest"
    print "soundFile..."
    newRecord.soundFile = "Fancy SOUN"
    newRecord.minDistance = 1
    newRecord.maxDistance = 55
    newRecord.freqAdjustment = -3
    newRecord.unused1 = 15
    newRecord.flags = 16
    newRecord.unused2 = [0x01, 0xFF]
    newRecord.staticAtten = 5
    newRecord.stopTime = 12
    newRecord.startTime = 24
    
    print "SOUN:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "soundFile      :", newRecord.soundFile
    print "minDistance    :", newRecord.minDistance
    print "maxDistance    :", newRecord.maxDistance
    print "freqAdjustment :", newRecord.freqAdjustment
    print "unused1        :", newRecord.unused1
    print "flags          :", newRecord.flags
    print "unused2        :", newRecord.unused2
    print "staticAtten    :", newRecord.staticAtten
    print "stopTime       :", newRecord.stopTime
    print "startTime      :", newRecord.startTime

    print "SOUN:CopyAsOverride Test"
    for record in Current[0].SOUN:
        record.CopyAsOverride(newMod)

    print "SOUN:CopyAsNew Test"
    for record in Current[0].SOUN:
        record.CopyAsNew(newMod)

    print "SOUN:Save Test - TestSOUN.esp"
    newMod.safeSave()
    print "SOUN:Finished testing"

def TestSKIL():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSKIL.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.SKIL:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        
        print "skill          :", record.skill
        print "description    :", record.description
        print "iconPath       :", record.iconPath
        print "action         :", record.action
        print "attribute      :", record.attribute
        print "specialization :", record.specialization
        print "use0           :", record.use0
        print "use1           :", record.use1
        print "apprentice     :", record.apprentice
        print "journeyman     :", record.journeyman
        print "expert         :", record.expert
        print "master         :", record.master

    print "SKIL:Create Record Test"
    newRecord = newMod.createSKILRecord()
    print "SKIL:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SKILWarTest"
    print "skill..."
    newRecord.skill = 1
    newRecord.description = "Fancy SKIL"
    newRecord.iconPath = r"ICON\Path\1.dds"
    newRecord.action = 2
    newRecord.attribute = 28
    newRecord.specialization = 1
    newRecord.use0 = 1.0
    newRecord.use1 = 2.0
    newRecord.apprentice = "of nothing"
    newRecord.journeyman = "Little bit"
    newRecord.expert = "Jack of none"
    newRecord.master = "Master of all"
    
    print "SKIL:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "skill          :", newRecord.skill
    print "description    :", newRecord.description
    print "iconPath       :", newRecord.iconPath
    print "action         :", newRecord.action
    print "attribute      :", newRecord.attribute
    print "specialization :", newRecord.specialization
    print "use0           :", newRecord.use0
    print "use1           :", newRecord.use1
    print "apprentice     :", newRecord.apprentice
    print "journeyman     :", newRecord.journeyman
    print "expert         :", newRecord.expert
    print "master         :", newRecord.master

    print "SKIL:CopyAsOverride Test"
    for record in Current[0].SKIL:
        record.CopyAsOverride(newMod)

    print "SKIL:CopyAsNew Test"
    for record in Current[0].SKIL:
        record.CopyAsNew(newMod)

    print "SKIL:Save Test - TestSKIL.esp"
    newMod.safeSave()
    print "SKIL:Finished testing"
def TestMGEF():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestMGEF.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.MGEF:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        
        print "full            :", record.full
        print "text            :", record.text
        print "iconPath        :", record.iconPath
        print "modPath         :", record.modPath
        print "modb            :", record.modb
        print "modt_p          :", record.modt_p
        print "flags           :", record.flags
        print "baseCost        :", record.baseCost
        print "associated      : %08X" % record.associated
        print "school          :", record.school
        print "resistValue     :", record.resistValue
        print "unk1            :", record.unk1
        print "unused1         :", record.unused1
        print "light           : %08X" % record.light
        print "projectileSpeed :", record.projectileSpeed
        print "effectShader    : %08X" % record.effectShader
        print "enchantEffect   : %08X" % record.enchantEffect
        print "castingSound    : %08X" % record.castingSound
        print "boltSound       : %08X" % record.boltSound
        print "hitSound        : %08X" % record.hitSound
        print "areaSound       : %08X" % record.areaSound
        print "cefEnchantment  :", record.cefEnchantment
        print "cefBarter       :", record.cefBarter
        print "counterEffects  :"
        for effect in record.counterEffects:
            print "  ", string_at(addressof(c_uint(effect)), 4)
        break
    print "MGEF:Create Record Test"
    newRecord = newMod.createMGEFRecord()
    print "MGEF:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "MGEFWarTest"
    newRecord.full = "Long winded and boring story"
    newRecord.text = "These can't be added anyway"
    newRecord.iconPath = "WHAT?"
    newRecord.modPath = "STILL?"
    newRecord.modb = 1.2
    newRecord.flags = 1
    newRecord.baseCost = 12
    newRecord.associated = 7
    newRecord.school = 30
    newRecord.resistValue = 35
    newRecord.unk1 = 15
    newRecord.light = 8
    newRecord.projectileSpeed = 9
    newRecord.effectShader = 10
    newRecord.enchantEffect = 11
    newRecord.castingSound = 12
    newRecord.boltSound = 13
    newRecord.hitSound = 14
    newRecord.areaSound = 15
    newRecord.cefEnchantment = 16.0
    newRecord.cefBarter = 17.2
    newRecord.counterEffects = [1280332612]
    
    print "MGEF:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "full            :", newRecord.full
    print "text            :", newRecord.text
    print "iconPath        :", newRecord.iconPath
    print "modPath         :", newRecord.modPath
    print "modb            :", newRecord.modb
    print "modt_p          :", newRecord.modt_p
    print "flags           :", newRecord.flags
    print "baseCost        :", newRecord.baseCost
    print "associated      : %08X" % newRecord.associated
    print "school          :", newRecord.school
    print "resistValue     :", newRecord.resistValue
    print "unk1            :", newRecord.unk1
    print "unused1         :", newRecord.unused1
    print "light           : %08X" % newRecord.light
    print "projectileSpeed :", newRecord.projectileSpeed
    print "effectShader    : %08X" % newRecord.effectShader
    print "enchantEffect   : %08X" % newRecord.enchantEffect
    print "castingSound    : %08X" % newRecord.castingSound
    print "boltSound       : %08X" % newRecord.boltSound
    print "hitSound        : %08X" % newRecord.hitSound
    print "areaSound       : %08X" % newRecord.areaSound
    print "cefEnchantment  :", newRecord.cefEnchantment
    print "cefBarter       :", newRecord.cefBarter
    print "counterEffects  :"
    for effect in newRecord.counterEffects:
        print "  ", string_at(addressof(c_uint(effect)), 4)

    print "MGEF:CopyAsOverride Test"
    for record in Current[0].MGEF:
        record.CopyAsOverride(newMod)

    print "MGEF:CopyAsNew Test"
    for record in Current[0].MGEF:
        record.CopyAsNew(newMod)

    print "MGEF:Save Test - TestMGEF.esp"
    newMod.safeSave()
    print "MGEF:Finished testing"
def TestSCPT():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSCPT.esp", True)
    Current.minimalLoad(LoadMasters=True)
    x = 0
    for record in Current.SCPT:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        
        print "unused1      :", record.unused1
        print "numRefs      :", record.numRefs
        print "compiledSize :", record.compiledSize
        print "lastIndex    :", record.lastIndex
        print "scriptType   :", record.scriptType
        print "compiled_p   :", record.compiled_p
        print "scriptText   :\n", record.scriptText
        print "vars"
        for var in record.vars:
            print
            print "  index   :", var.index
            print "  unused1 :", var.unused1
            print "  flags   :", var.flags
            print "  unused2 :", var.unused2
            print "  name    :", var.name
        print "references"
        for reference in record.references:
            if(reference.isSCRO):
                print "  SCRO: %08X" % reference.reference
            else:
                print "  SCRV:", reference.reference
        break

    print "SCPT:Create Record Test"
    newRecord = newMod.createSCPTRecord()
    print "SCPT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SCPTWarTest"

    newRecord.unused1 = [0x0F, 0xFF]
    newRecord.numRefs = 0
    newRecord.compiledSize = 2
    newRecord.lastIndex = 1
    newRecord.scriptType = 1
    newRecord.compiled_p = [0x00, 0xFF]
    newRecord.scriptText = "scn WarTest\nshort Didit\nend"

    newRelation = newRecord.newVarsElement()
    newRelation.index = 1
    newRelation.unused1 = [0,1,2,3,4,5,6,7,8,9,10,11]
    newRelation.flags = 1
    newRelation.unused2 = [0,1,2,3,4,5,6]
    newRelation.name = "Didit"

    newRelation = newRecord.newVarsElement()
    newRelation.index = 2
    newRelation.unused1 = [0,1,2,3,4,5,6,7,8,9,10,11]
    newRelation.flags = 2
    newRelation.unused2 = [0,1,2,3,4,5,6]
    newRelation.name = "Did1it"
    
    newRelation = newRecord.newVarsElement()
    newRelation.index = 3
    newRelation.unused1 = [0,1,2,3,4,5,6,7,8,9,10,11]
    newRelation.flags = 2
    newRelation.unused2 = [0,1,2,3,4,5,6]
    newRelation.name = "Did2it"
        
    newReference = newRecord.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True

    newReference = newRecord.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    newReference = newRecord.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = 1
    newReference = newRecord.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO =0

    print "SCPT:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "unused1      :", newRecord.unused1
    print "numRefs      :", newRecord.numRefs
    print "compiledSize :", newRecord.compiledSize
    print "lastIndex    :", newRecord.lastIndex
    print "scriptType   :", newRecord.scriptType
    print "compiled_p   :", newRecord.compiled_p
    print "scriptText   :\n", newRecord.scriptText
    print "vars         :"
    for var in newRecord.vars:
        print
        print "  index   :", var.index
        print "  unused1 :", var.unused1
        print "  flags   :", var.flags
        print "  unused2 :", var.unused2
        print "  name    :", var.name
    print "references   :"
    for reference in newRecord.references:
        if(reference.isSCRO):
            print "  SCRO: %08X" % reference.reference
        else:
            print "  SCRV:", reference.reference

    print "SCPT:CopyAsOverride Test"
    for record in Current[0].SCPT:
        record.CopyAsOverride(newMod)

    print "SCPT:CopyAsNew Test"
    for record in Current[0].SCPT:
        record.CopyAsNew(newMod)

    print "SCPT:Save Test - TestSCPT.esp"
    newMod.safeSave()
    print "SCPT:Finished testing"


def TestLTEX():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLTEX.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.LTEX:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "iconPath    :", record.iconPath
        print "flags       :", record.flags
        print "friction    :", record.friction
        print "restitution :", record.restitution
        print "specular    :", record.specular
        print "grass    :"
        for grass in record.grass:
            print "  %08X" % grass
        break

    print "LTEX:Create Record Test"
    newRecord = newMod.createLTEXRecord()
    print "LTEX:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."

    newRecord.eid = "LTEXWarTest"
    newRecord.iconPath = r"LTEX\path\test.dds"
    newRecord.flags = 156
    newRecord.friction = 111
    newRecord.restitution = 123
    newRecord.specular = 128

    newRecord.grass = [0xFF000121, 0xFE000222]

    
    print "LTEX:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "iconPath    :", newRecord.iconPath
    print "flags       :", newRecord.flags
    print "friction    :", newRecord.friction
    print "restitution :", newRecord.restitution
    print "specular    :", newRecord.specular
    print "grass    :"
    for grass in newRecord.grass:
        print "  %08X" % grass
            
    print "LTEX:CopyAsOverride Test"
    for record in Current[0].LTEX:
        record.CopyAsOverride(newMod)

    print "LTEX:CopyAsNew Test"
    for record in Current[0].LTEX:
        record.CopyAsNew(newMod)

    print "LTEX:Save Test - TestLTEX.esp"
    newMod.safeSave()
    print "LTEX:Finished testing"


def TestENCH():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestENCH.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.ENCH:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full         :", record.full
        print "itemType     :", record.itemType
        print "chargeAmount :", record.chargeAmount
        print "enchantCost  :", record.enchantCost
        print "flags        :", record.flags
        print "unused1      :", record.unused1
        print "effects :"
        for effect in record.effects:
            print "  name0      :", effect.name0
            print "  name       :", effect.name
            print "  magnitude  :", effect.magnitude
            print "  area       :", effect.area
            print "  duration   :", effect.duration
            print "  recipient  :", effect.recipient
            print "  actorValue :", effect.actorValue
            print "  script     : %08X" % effect.script
            print "  school     :", effect.school
            print "  visual     :", effect.visual
            print "  flags      :", effect.flags
            print "  unused1    :", effect.unused1
            print "  full       :", effect.full
            print
        break

    print "ENCH:Create Record Test"
    newRecord = newMod.createENCHRecord()
    print "ENCH:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "ENCHWarTest"

    newRecord.full = "Fancy ENCH"
    newRecord.itemType = 1
    newRecord.chargeAmount = 2
    newRecord.enchantCost = 3
    newRecord.flags = 4
    newRecord.unused1 = [0,1,2]

    newEffect = newRecord.newEffectsElement()
    newEffect.name0 = 0x52474E49
    newEffect.name = 0x53414C43
    newEffect.magnitude = 1
    newEffect.area = 2
    newEffect.duration = 3
    newEffect.recipient = 4
    newEffect.actorValue = 5
    newEffect.script = 0xFF000007
    newEffect.school = 324
    newEffect.visual = 0x53414C43
    newEffect.flags = 16
    newEffect.unused1 = [3,4,5]
    newEffect.full = "ENCH?"

    newEffect = newRecord.newEffectsElement()
    newEffect.name0 = 0x52474E49
    newEffect.name = 0x48434E45
    newEffect.magnitude = 6
    newEffect.area = 7
    newEffect.duration = 8
    newEffect.recipient = 9
    newEffect.actorValue = 10
    newEffect.script = 0xFF00000A
    newEffect.school = 11
    newEffect.visual = 0x48434E45
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "ENCH??"
    print "ENCH:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full         :", newRecord.full
    print "itemType     :", newRecord.itemType
    print "chargeAmount :", newRecord.chargeAmount
    print "enchantCost  :", newRecord.enchantCost
    print "flags        :", newRecord.flags
    print "unused1      :", newRecord.unused1
    print "effects :"
    for effect in newRecord.effects:
        print "  name0      :", effect.name0
        print "  name       :", effect.name
        print "  magnitude  :", effect.magnitude
        print "  area       :", effect.area
        print "  duration   :", effect.duration
        print "  recipient  :", effect.recipient
        print "  actorValue :", effect.actorValue
        print "  script     : %08X" % effect.script
        print "  school     :", effect.school
        print "  visual     :", effect.visual
        print "  flags      :", effect.flags
        print "  unused1    :", effect.unused1
        print "  full       :", effect.full
        print
    print "ENCH:CopyAsOverride Test"
    for record in Current[0].ENCH:
        record.CopyAsOverride(newMod)

    print "ENCH:CopyAsNew Test"
    for record in Current[0].ENCH:
        record.CopyAsNew(newMod)

    print "ENCH:Save Test - TestENCH.esp"
    newMod.safeSave()
    print "ENCH:Finished testing"


def TestSPEL():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSPEL.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.SPEL:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full         :", record.full
        print "spellType    :", record.spellType
        print "cost         :", record.cost
        print "level        :", record.level
        print "flags        :", record.flags
        print "unused1      :", record.unused1
        print "effects :"
        for effect in record.effects:
            print "  name0      :", effect.name0
            print "  name       :", effect.name
            print "  magnitude  :", effect.magnitude
            print "  area       :", effect.area
            print "  duration   :", effect.duration
            print "  recipient  :", effect.recipient
            print "  actorValue :", effect.actorValue
            print "  script     : %08X" % effect.script
            print "  school     :", effect.school
            print "  visual     :", effect.visual
            print "  flags      :", effect.flags
            print "  unused1    :", effect.unused1
            print "  full       :", effect.full
            print
        break

    print "SPEL:Create Record Test"
    newRecord = newMod.createSPELRecord()
    print "SPEL:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SPELWarTest"

    newRecord.full = "Fancy SPEL"
    newRecord.spellType = 1
    newRecord.cost = 2
    newRecord.level = 3
    newRecord.flags = 4
    newRecord.unused1 = [0,1,2]

    newEffect = newRecord.newEffectsElement()
    newEffect.name0 = 0x4C455053
    newEffect.name = 0x53414C43
    newEffect.magnitude = 1
    newEffect.area = 2
    newEffect.duration = 3
    newEffect.recipient = 4
    newEffect.actorValue = 5
    newEffect.script = 0xFF000007
    newEffect.school = 324
    newEffect.visual = 0x53414C43
    newEffect.flags = 16
    newEffect.unused1 = [3,4,5]
    newEffect.full = "SPEL?"

    newEffect = newRecord.newEffectsElement()
    newEffect.name0 = 0x52474E49
    newEffect.name = 0x4C455053
    newEffect.magnitude = 6
    newEffect.area = 7
    newEffect.duration = 8
    newEffect.recipient = 9
    newEffect.actorValue = 10
    newEffect.script = 0xFF00000A
    newEffect.school = 11
    newEffect.visual = 0x4C455053
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "SPEL??"
    print "SPEL:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full         :", newRecord.full
    print "spellType    :", newRecord.spellType
    print "cost         :", newRecord.cost
    print "level        :", newRecord.level
    print "flags        :", newRecord.flags
    print "unused1      :", newRecord.unused1
    print "effects :"
    for effect in newRecord.effects:
        print "  name0      :", effect.name0
        print "  name       :", effect.name
        print "  magnitude  :", effect.magnitude
        print "  area       :", effect.area
        print "  duration   :", effect.duration
        print "  recipient  :", effect.recipient
        print "  actorValue :", effect.actorValue
        print "  script     : %08X" % effect.script
        print "  school     :", effect.school
        print "  visual     :", effect.visual
        print "  flags      :", effect.flags
        print "  unused1    :", effect.unused1
        print "  full       :", effect.full
        print
    print "SPEL:CopyAsOverride Test"
    for record in Current[0].SPEL:
        record.CopyAsOverride(newMod)

    print "SPEL:CopyAsNew Test"
    for record in Current[0].SPEL:
        record.CopyAsNew(newMod)

    print "SPEL:Save Test - TestSPEL.esp"
    newMod.safeSave()
    print "SPEL:Finished testing"

def TestBSGN():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestBSGN.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.BSGN:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full      :", record.full
        print "iconPath  :", record.iconPath
        print "text      :", record.text
        print "spells    :"
        for spell in record.spells:
            print "  %08X" % spell
        break

    print "BSGN:Create Record Test"
    newRecord = newMod.createBSGNRecord()
    print "BSGN:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "BSGNWarTest"
    newRecord.full = "Fancy BSGN"

    newRecord.iconPath = r"BSGN\p\nath\test.dds"
    newRecord.text = "BLAH BLAH BLHARGH"
    newRecord.spells = [0xFF000121, 0xFE000222]
    print "BSGN:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "full      :", newRecord.full
    print "iconPath  :", newRecord.iconPath
    print "text      :", newRecord.text
    print "spells    :"
    for spell in newRecord.spells:
        print "  %08X" % spell
    print "BSGN:CopyAsOverride Test"
    for record in Current[0].BSGN:
        record.CopyAsOverride(newMod)

    print "BSGN:CopyAsNew Test"
    for record in Current[0].BSGN:
        record.CopyAsNew(newMod)

    print "BSGN:Save Test - TestBSGN.esp"
    newMod.safeSave()
    print "BSGN:Finished testing"



def TestACTI():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestACTI.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.ACTI:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "script  :", record.script
        print "sound   :", record.sound
        break

    print "ACTI:Create Record Test"
    newRecord = newMod.createACTIRecord()
    print "ACTI:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "ACTIWarTest"
    print "full..."
    newRecord.full = "Fancy ACTI"

    print "modPath..."
    newRecord.modPath = r"ACTI\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    newRecord.script = 7
    newRecord.sound = 0x0000000A
    
    print "ACTI:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p
    print "script  :", newRecord.script
    print "sound   :", newRecord.sound
    
    print "ACTI:CopyAsOverride Test"
    for record in Current[0].ACTI:
        record.CopyAsOverride(newMod)

    print "ACTI:CopyAsNew Test"
    for record in Current[0].ACTI:
        record.CopyAsNew(newMod)

    print "ACTI:Save Test - TestACTI.esp"
    newMod.safeSave()
    print "ACTI:Finished testing"


def TestAPPA():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestAPPA.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.APPA:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "iconPath  :", record.iconPath
        print "script    :", record.script
        print "apparatus :", record.apparatus
        print "value     :", record.value
        print "weight    :", record.weight
        print "quality   :", record.quality
        break

    print "APPA:Create Record Test"
    newRecord = newMod.createAPPARecord()
    print "APPA:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "APPAWarTest"
    print "full..."
    newRecord.full = "Fancy APPA"

    print "modPath..."
    newRecord.modPath = r"APPA\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "iconPath..."
    newRecord.iconPath = r"APPA\path\test.dds"
    newRecord.script = 7
    newRecord.apparatus = 1
    newRecord.value = 150
    newRecord.weight = 3.56
    newRecord.quality = 3.0
    print "APPA:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full      :", newRecord.full
    print "modPath   :", newRecord.modPath
    print "modb      :", newRecord.modb
    print "modt_p    :", newRecord.modt_p
    print "iconPath  :", newRecord.iconPath
    print "script    :", newRecord.script
    print "apparatus :", newRecord.apparatus
    print "value     :", newRecord.value
    print "weight    :", newRecord.weight
    print "quality   :", newRecord.quality
    
    print "APPA:CopyAsOverride Test"
    for record in Current[0].APPA:
        record.CopyAsOverride(newMod)

    print "APPA:CopyAsNew Test"
    for record in Current[0].APPA:
        record.CopyAsNew(newMod)

    print "APPA:Save Test - TestAPPA.esp"
    newMod.safeSave()
    print "APPA:Finished testing"


def TestARMO():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestARMO.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.ARMO:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full          :", record.full
        print "script        : %08X" % record.script
        print "enchantment   : %08X" % record.enchantment
        print "enchantPoints :", record.enchantPoints
        print "flags         :", record.flags
        print "maleBody.modPath  :", record.maleBody.modPath
        print "maleBody.modb     :", record.maleBody.modb
        print "maleBody.modt_p   :", record.maleBody.modt_p
        print "maleWorld.modPath :", record.maleWorld.modPath
        print "maleWorld.modb    :", record.maleWorld.modb
        print "maleWorld.modt_p  :", record.maleWorld.modt_p
        print "maleIconPath      :", record.maleIconPath
        print "femaleBody.modPath  :", record.femaleBody.modPath
        print "femaleBody.modb     :", record.femaleBody.modb
        print "femaleBody.modt_p   :", record.femaleBody.modt_p
        print "femaleWorld.modPath :", record.femaleWorld.modPath
        print "femaleWorld.modb    :", record.femaleWorld.modb
        print "femaleWorld.modt_p  :", record.femaleWorld.modt_p
        print "femaleIconPath      :", record.femaleIconPath
        print "strength       :", record.strength
        print "value          :", record.value
        print "health         :", record.health
        print "weight         :", record.weight

        break

    print "ARMO:Create Record Test"
    newRecord = newMod.createARMORecord()
    print "ARMO:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "ARMOWarTest"

    newRecord.full =  "Fancy ARMO"
    newRecord.script = 7
    newRecord.enchantment = 0x0000000A
    newRecord.enchantPoints = 251
    newRecord.flags = 1
    newRecord.maleBody.modPath = r"maleBody\hay\1.nif"
    newRecord.maleBody.modb = 1.1
    newRecord.maleBody.modt_p = [0x00, 0xFF, 0xFE]
    newRecord.maleWorld.modPath = r"maleWorld\hay\1.nif"
    newRecord.maleWorld.modb = 1.2
    newRecord.maleWorld.modt_p = [0x00, 0xFF, 0xFD]
    newRecord.maleIconPath = r"maleIconPath\hay\1.dds"
    newRecord.femaleBody.modPath = r"femaleBody\hay\1.nif"
    newRecord.femaleBody.modb = 1.3
    newRecord.femaleBody.modt_p = [0x00, 0xFF, 0xFC]
    newRecord.femaleWorld.modPath = r"femaleWorld\hay\1.nif"
    newRecord.femaleWorld.modb = 1.4
    newRecord.femaleWorld.modt_p = [0x00, 0xFF, 0xFB]
    newRecord.femaleIconPath =  r"femaleIconPath\hay\1.dds"
    newRecord.strength = 15
    newRecord.value = 150
    newRecord.health = 155
    newRecord.weight = 5

        
    print "ARMO:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full          :", newRecord.full
    print "script        : %08X" % newRecord.script
    print "enchantment   : %08X" % newRecord.enchantment
    print "enchantPoints :", newRecord.enchantPoints
    print "flags         :", newRecord.flags
    print "maleBody.modPath  :", newRecord.maleBody.modPath
    print "maleBody.modb     :", newRecord.maleBody.modb
    print "maleBody.modt_p   :", newRecord.maleBody.modt_p
    print "maleWorld.modPath :", newRecord.maleWorld.modPath
    print "maleWorld.modb    :", newRecord.maleWorld.modb
    print "maleWorld.modt_p  :", newRecord.maleWorld.modt_p
    print "maleIconPath      :", newRecord.maleIconPath
    print "femaleBody.modPath  :", newRecord.femaleBody.modPath
    print "femaleBody.modb     :", newRecord.femaleBody.modb
    print "femaleBody.modt_p   :", newRecord.femaleBody.modt_p
    print "femaleWorld.modPath :", newRecord.femaleWorld.modPath
    print "femaleWorld.modb    :", newRecord.femaleWorld.modb
    print "femaleWorld.modt_p  :", newRecord.femaleWorld.modt_p
    print "femaleIconPath      :", newRecord.femaleIconPath
    print "strength       :", newRecord.strength
    print "value          :", newRecord.value
    print "health         :", newRecord.health
    print "weight         :", newRecord.weight
    print "ARMO:CopyAsOverride Test"
    for record in Current[0].ARMO:
        record.CopyAsOverride(newMod)

    print "ARMO:CopyAsNew Test"
    for record in Current[0].ARMO:
        record.CopyAsNew(newMod)

    print "ARMO:Save Test - TestARMO.esp"
    newMod.safeSave()
    print "ARMO:Finished testing"


def TestBOOK():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestBOOK.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.BOOK:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "iconPath      :", record.iconPath
        print "text          :", record.text
        print "script        : %08X" % record.script
        print "enchantment   : %08X" % record.enchantment
        print "enchantPoints :", record.enchantPoints
        print "flags         :", record.flags
        print "teaches       :", record.teaches
        print "value         :", record.value
        print "weight        :", record.weight
        break

    print "BOOK:Create Record Test"
    newRecord = newMod.createBOOKRecord()
    print "BOOK:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "BOOKWarTest"
    print "full..."
    newRecord.full = "Fancy BOOK"

    print "modPath..."
    newRecord.modPath = r"BOOK\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "iconPath..."
    newRecord.iconPath = r"BOOK\path\test.dds"
    newRecord.text = "Now this is a story about...something. And an interesting thing happened to...something. But, unknown to...something..., there was opposition from...something else....\n<br>Hey!</br><herlmf></herlmf>\nJust a test\n"
    newRecord.script = 7
    newRecord.enchantment = 0x0000000A
    newRecord.enchantPoints = 251
    newRecord.flags = 1
    newRecord.teaches = -1
    newRecord.value = 152
    newRecord.weight = 3.56

    
    print "BOOK:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath      :", newRecord.iconPath
    print "text          :", newRecord.text
    print "script        : %08X" % newRecord.script
    print "enchantment   : %08X" % newRecord.enchantment
    print "enchantPoints :", newRecord.enchantPoints
    print "flags         :", newRecord.flags
    print "teaches       :", newRecord.teaches
    print "value         :", newRecord.value
    print "weight        :", newRecord.weight
    print "BOOK:CopyAsOverride Test"
    for record in Current[0].BOOK:
        record.CopyAsOverride(newMod)

    print "BOOK:CopyAsNew Test"
    for record in Current[0].BOOK:
        record.CopyAsNew(newMod)

    print "BOOK:Save Test - TestBOOK.esp"
    newMod.safeSave()
    print "BOOK:Finished testing"


def TestCLOT():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCLOT.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.CLOT:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full          :", record.full
        print "script        : %08X" % record.script
        print "enchantment   : %08X" % record.enchantment
        print "enchantPoints :", record.enchantPoints
        print "flags         :", record.flags
        print "maleBody.modPath  :", record.maleBody.modPath
        print "maleBody.modb     :", record.maleBody.modb
        print "maleBody.modt_p   :", record.maleBody.modt_p
        print "maleWorld.modPath :", record.maleWorld.modPath
        print "maleWorld.modb    :", record.maleWorld.modb
        print "maleWorld.modt_p  :", record.maleWorld.modt_p
        print "maleIconPath      :", record.maleIconPath
        print "femaleBody.modPath  :", record.femaleBody.modPath
        print "femaleBody.modb     :", record.femaleBody.modb
        print "femaleBody.modt_p   :", record.femaleBody.modt_p
        print "femaleWorld.modPath :", record.femaleWorld.modPath
        print "femaleWorld.modb    :", record.femaleWorld.modb
        print "femaleWorld.modt_p  :", record.femaleWorld.modt_p
        print "femaleIconPath      :", record.femaleIconPath
        print "value          :", record.value
        print "weight         :", record.weight

        break

    print "CLOT:Create Record Test"
    newRecord = newMod.createCLOTRecord()
    print "CLOT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CLOTWarTest"

    newRecord.full =  "Fancy CLOT"
    newRecord.script = 7
    newRecord.enchantment = 0x0000000A
    newRecord.enchantPoints = 251
    newRecord.flags = 1
    newRecord.maleBody.modPath = r"maleBody\hay\1.nif"
    newRecord.maleBody.modb = 1.1
    newRecord.maleBody.modt_p = [0x00, 0xFF, 0xFE]
    newRecord.maleWorld.modPath = r"maleWorld\hay\1.nif"
    newRecord.maleWorld.modb = 1.2
    newRecord.maleWorld.modt_p = [0x00, 0xFF, 0xFD]
    newRecord.maleIconPath = r"maleIconPath\hay\1.dds"
    newRecord.femaleBody.modPath = r"femaleBody\hay\1.nif"
    newRecord.femaleBody.modb = 1.3
    newRecord.femaleBody.modt_p = [0x00, 0xFF, 0xFC]
    newRecord.femaleWorld.modPath = r"femaleWorld\hay\1.nif"
    newRecord.femaleWorld.modb = 1.4
    newRecord.femaleWorld.modt_p = [0x00, 0xFF, 0xFB]
    newRecord.femaleIconPath =  r"femaleIconPath\hay\1.dds"
    newRecord.value = 151
    newRecord.weight = 6
    print "CLOT:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full          :", newRecord.full
    print "script        : %08X" % newRecord.script
    print "enchantment   : %08X" % newRecord.enchantment
    print "enchantPoints :", newRecord.enchantPoints
    print "flags         :", newRecord.flags
    print "maleBody.modPath  :", newRecord.maleBody.modPath
    print "maleBody.modb     :", newRecord.maleBody.modb
    print "maleBody.modt_p   :", newRecord.maleBody.modt_p
    print "maleWorld.modPath :", newRecord.maleWorld.modPath
    print "maleWorld.modb    :", newRecord.maleWorld.modb
    print "maleWorld.modt_p  :", newRecord.maleWorld.modt_p
    print "maleIconPath      :", newRecord.maleIconPath
    print "femaleBody.modPath  :", newRecord.femaleBody.modPath
    print "femaleBody.modb     :", newRecord.femaleBody.modb
    print "femaleBody.modt_p   :", newRecord.femaleBody.modt_p
    print "femaleWorld.modPath :", newRecord.femaleWorld.modPath
    print "femaleWorld.modb    :", newRecord.femaleWorld.modb
    print "femaleWorld.modt_p  :", newRecord.femaleWorld.modt_p
    print "femaleIconPath      :", newRecord.femaleIconPath
    print "value          :", newRecord.value
    print "weight         :", newRecord.weight
    print "CLOT:CopyAsOverride Test"
    for record in Current[0].CLOT:
        record.CopyAsOverride(newMod)

    print "CLOT:CopyAsNew Test"
    for record in Current[0].CLOT:
        record.CopyAsNew(newMod)

    print "CLOT:Save Test - TestCLOT.esp"
    newMod.safeSave()
    print "CLOT:Finished testing"


def TestCONT():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCONT.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.CONT:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "script     : %08X" % record.script
        print "items      :"
        for item in record.items:
            print "  %i: item: %08X, count: %i" % (item._listIndex, item.item, item.count)
        print "flags      :", record.flags
        print "weight     :", record.weight
        print "soundOpen  : %08X" % record.soundOpen
        print "soundClose : %08X" % record.soundClose

        break

    print "CONT:Create Record Test"
    newRecord = newMod.createCONTRecord()
    print "CONT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CONTWarTest"
    print "full..."
    newRecord.full = "Fancy CONT"

    print "modPath..."
    newRecord.modPath = r"CONT\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    newRecord.script = 7
    item = newRecord.newItemsElement()
    item.item = 0x0100000A
    item.count = 50
    item = newRecord.newItemsElement()
    item.item = 0x0000000B
    item.count = 1
    item = newRecord.newItemsElement()
    item.item = 0x0000000C
    item.count = 2
    item = newRecord.newItemsElement()
    item.item = 0x0000000D
    item.count = 3
    newRecord.items = [newRecord.items[3], newRecord.items[2], newRecord.items[0]]
    newRecord.flags = 1
    newRecord.weight = 3.56
    newRecord.soundOpen  = 0x00000007
    newRecord.soundClose = 0x00000008

    print "CONT:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "script     : %08X" % newRecord.script
    print "items      :"
    for item in newRecord.items:
        print "  %i: item: %08X, count: %i" % (item._listIndex, item.item, item.count)
    print "flags      :", newRecord.flags
    print "weight     :", newRecord.weight
    print "soundOpen  : %08X" % newRecord.soundOpen
    print "soundClose : %08X" % newRecord.soundClose
        
    print "CONT:CopyAsOverride Test"
    for record in Current[0].CONT:
        record.CopyAsOverride(newMod)

    print "CONT:CopyAsNew Test"
    for record in Current[0].CONT:
        record.CopyAsNew(newMod)

    print "CONT:Save Test - TestCONT.esp"
    newMod.safeSave()
    print "CONT:Finished testing"


def TestDOOR():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestDOOR.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.DOOR:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        
        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "script     : %08X" % record.script
        print "soundOpen  : %08X" % record.soundOpen
        print "soundClose : %08X" % record.soundClose
        print "soundLoop  : %08X" % record.soundLoop

        print "flags   :", record.flags
        print "destinations :"
        for destination in record.destinations:
            print "  %08X" % destination
        break

    print "DOOR:Create Record Test"
    newRecord = newMod.createDOORRecord()
    print "DOOR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "DOORWarTest"
    print "full..."
    newRecord.full = "Fancy DOOR"

    print "modPath..."
    newRecord.modPath = r"DOOR\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.1
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    newRecord.script = 8
    newRecord.soundOpen  = 0x00000007
    newRecord.soundClose = 0x00000008
    newRecord.soundLoop = 0x00000009

    newRecord.flags = 1
    newRecord.destinations = [0xFF000121, 0xFE000222]
    print "DOOR:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "script     : %08X" % newRecord.script
    print "soundOpen  : %08X" % newRecord.soundOpen
    print "soundClose : %08X" % newRecord.soundClose
    print "soundLoop  : %08X" % newRecord.soundLoop

    print "flags   :", newRecord.flags
    print "destinations :"
    for destination in newRecord.destinations:
        print "  %08X" % destination

    print "DOOR:CopyAsOverride Test"
    for record in Current[0].DOOR:
        record.CopyAsOverride(newMod)

    print "DOOR:CopyAsNew Test"
    for record in Current[0].DOOR:
        record.CopyAsNew(newMod)

    print "DOOR:Save Test - TestDOOR.esp"
    newMod.safeSave()
    print "DOOR:Finished testing"


def TestINGR():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestINGR.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.INGR:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "iconPath:", record.iconPath
        print "script  : %08X" % record.script
        print "weight  :", record.weight
        print "value   :", record.value
        print "flags   :", record.flags
        
        print "unused1 :", record.unused1
        
        print "effects :"
        for effect in record.effects:
            print "  name0      :", effect.name0
            print "  name       :", effect.name
            print "  magnitude  :", effect.magnitude
            print "  area       :", effect.area
            print "  duration   :", effect.duration
            print "  recipient  :", effect.recipient
            print "  actorValue :", effect.actorValue
            print "  script     : %08X" % effect.script
            print "  school     :", effect.school
            print "  visual     :", effect.visual
            print "  flags      :", effect.flags
            print "  unused1    :", effect.unused1
            print "  full       :", effect.full
            print
        break

    print "INGR:Create Record Test"
    newRecord = newMod.createINGRRecord()
    print "INGR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "INGRWarTest"
    print "full..."
    newRecord.full = "Fancy INGR"

    print "modPath..."
    newRecord.modPath = r"INGR\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "iconPath..."
    newRecord.iconPath = r"INGR\path\test.dds"
    newRecord.script = 7
    newRecord.weight = 3.56
    newRecord.value = 150

    newRecord.flags = 1
    
    newRecord.unused1 = [0x00, 0xFE, 0xFD]

    newEffect = newRecord.newEffectsElement()
    newEffect.name0 = 0x52474E49
    newEffect.name = 0x53414C43
    newEffect.magnitude = 1
    newEffect.area = 2
    newEffect.duration = 3
    newEffect.recipient = 4
    newEffect.actorValue = 5
    newEffect.script = 0xFF000007
    newEffect.school = 324
    newEffect.visual = 0x52474E49
    newEffect.flags = 16
    newEffect.unused1 = [3,4,5]
    newEffect.full = "INGR?"

    newEffect = newRecord.newEffectsElement()
    newEffect.name0 = 0x52474E49
    newEffect.name = 0x52474E49
    newEffect.magnitude = 6
    newEffect.area = 7
    newEffect.duration = 8
    newEffect.recipient = 9
    newEffect.actorValue = 10
    newEffect.script = 0xFF00000A
    newEffect.school = 11
    newEffect.visual = 0x4C455053
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "INGR??"
    
    print "INGR:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath:", newRecord.iconPath
    print "script  : %08X" % newRecord.script
    print "weight  :", newRecord.weight
    print "value   :", newRecord.value
    print "flags   :", newRecord.flags
    
    print "unused1 :", newRecord.unused1
    
    print "effects :"
    for effect in newRecord.effects:
        print "  name0      :", effect.name0
        print "  name       :", effect.name
        print "  magnitude  :", effect.magnitude
        print "  area       :", effect.area
        print "  duration   :", effect.duration
        print "  recipient  :", effect.recipient
        print "  actorValue :", effect.actorValue
        print "  script     : %08X" % effect.script
        print "  school     :", effect.school
        print "  visual     :", effect.visual
        print "  flags      :", effect.flags
        print "  unused1    :", effect.unused1
        print "  full       :", effect.full
        print    
    print "INGR:CopyAsOverride Test"
    for record in Current[0].INGR:
        record.CopyAsOverride(newMod)

    print "INGR:CopyAsNew Test"
    for record in Current[0].INGR:
        record.CopyAsNew(newMod)

    print "INGR:Save Test - TestINGR.esp"
    newMod.safeSave()
    print "INGR:Finished testing"


def TestLIGH():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLIGH.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.LIGH:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p
        print "script  : %08X" % record.script
        print "full    :", record.full
        print "iconPath:", record.iconPath
        print "duration:", record.duration
        print "radius  :", record.radius

        print "red     :", record.red
        print "green   :", record.green
        print "blue    :", record.blue
        print "unused1 :", record.unused1
        
        print "flags   :", record.flags
        print "falloff :", record.falloff
        print "fov     :", record.fov
        print "value   :", record.value
        print "weight  :", record.weight
        print "fade    :", record.fade
        print "sound   : %08X" % record.sound
        break

    print "LIGH:Create Record Test"
    newRecord = newMod.createLIGHRecord()
    print "LIGH:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "LIGHWarTest"

    print "modPath..."
    newRecord.modPath = r"LIGH\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.26
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    newRecord.script = 7

    print "full..."
    newRecord.full = "Fancy LIGH"
    print "iconPath..."
    newRecord.iconPath = r"LIGH\path\test.dds"
    
    newRecord.duration = -1
    newRecord.radius = 256
    
    newRecord.red = 70
    newRecord.green = 71
    newRecord.blue = 72
    newRecord.unused1 = [12]
    
    newRecord.flags = 1
    newRecord.falloff = 12.6
    newRecord.fov = 35.1
    newRecord.value = 70
    newRecord.weight = 5.2
    newRecord.fade = 6.9
    newRecord.sound = 14

    print "LIGH:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p
    print "script  : %08X" % newRecord.script
    print "full    :", newRecord.full
    print "iconPath:", newRecord.iconPath
    print "duration:", newRecord.duration
    print "radius  :", newRecord.radius

    print "red     :", newRecord.red
    print "green   :", newRecord.green
    print "blue    :", newRecord.blue
    print "unused1 :", newRecord.unused1
    
    print "flags   :", newRecord.flags
    print "falloff :", newRecord.falloff
    print "fov     :", newRecord.fov
    print "value   :", newRecord.value
    print "weight  :", newRecord.weight
    print "fade    :", newRecord.fade
    print "sound   : %08X" % newRecord.sound
        
    print "LIGH:CopyAsOverride Test"
    for record in Current[0].LIGH:
        record.CopyAsOverride(newMod)

    print "LIGH:CopyAsNew Test"
    for record in Current[0].LIGH:
        record.CopyAsNew(newMod)

    print "LIGH:Save Test - TestLIGH.esp"
    newMod.safeSave()
    print "LIGH:Finished testing"


def TestMISC():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestMISC.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.MISC:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "iconPath:", record.iconPath
        print "script  : %08X" % record.script
        print "value   :", record.value
        print "weight  :", record.weight
        break

    print "MISC:Create Record Test"
    newRecord = newMod.createMISCRecord()
    print "MISC:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "MISCWarTest"
    print "full..."
    newRecord.full = "Fancy MISC"

    print "modPath..."
    newRecord.modPath = r"Blah\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "iconPath..."
    newRecord.iconPath = r"MISC\path\test.dds"
    newRecord.script = 7
    newRecord.value = 150
    newRecord.weight = 3.56

    print "MISC:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p
    print "iconPath:", newRecord.iconPath
    print "script  :", newRecord.script
    print "value   :", newRecord.value
    print "weight  :", newRecord.weight
    
    print "MISC:CopyAsOverride Test"
    for record in Current[0].MISC:
        record.CopyAsOverride(newMod)

    print "MISC:CopyAsNew Test"
    for record in Current[0].MISC:
        record.CopyAsNew(newMod)

    print "MISC:Save Test - TestMISC.esp"
    newMod.safeSave()
    print "MISC:Finished testing"

def TestSTAT():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSTAT.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.STAT:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p
        break

    print "STAT:Create Record Test"
    newRecord = newMod.createSTATRecord()
    print "STAT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "STATWarTest"

    print "modPath..."
    newRecord.modPath = r"STAT\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.16
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "STAT:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p
    
    print "STAT:CopyAsOverride Test"
    for record in Current[0].STAT:
        record.CopyAsOverride(newMod)

    print "STAT:CopyAsNew Test"
    for record in Current[0].STAT:
        record.CopyAsNew(newMod)

    print "STAT:Save Test - TestSTAT.esp"
    newMod.safeSave()
    print "STAT:Finished testing"

def TestGRAS():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestGRAS.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.GRAS:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p
        
        print "density       :", record.density
        print "minSlope      :", record.minSlope
        print "maxSlope      :", record.maxSlope
        print "unused1       :", record.unused1
        print "waterDistance :", record.waterDistance
        print "unused2       :", record.unused2
        print "waterOp       :", record.waterOp
        print "posRange      :", record.posRange
        print "heightRange   :", record.heightRange
        print "colorRange    :", record.colorRange
        print "wavePeriod    :", record.wavePeriod
        print "flags         :", record.flags
        print "unused3       :", record.unused3
        break

    print "GRAS:Create Record Test"
    newRecord = newMod.createGRASRecord()
    print "GRAS:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "GRASWarTest"
    
    newRecord.modPath = r"GRAS\path\test.nif"
    newRecord.modb = 1.5
    newRecord.modt_p = [0xFF, 0x00, 0xFE]
    newRecord.density = 1
    newRecord.minSlope = 1
    newRecord.maxSlope = 255
    newRecord.unused1 = [1]
    newRecord.waterDistance = 300
    newRecord.unused2 = [0xFF, 0xFE]
    newRecord.waterOp = 5
    newRecord.posRange = 1.2
    newRecord.heightRange = 1.3
    newRecord.colorRange = 1.4
    newRecord.wavePeriod = 1.5
    newRecord.flags = 1
    newRecord.unused3 = [0xFF, 0x00, 0xFE]
    
    print "GRAS:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p
        
    print "density       :", newRecord.density
    print "minSlope      :", newRecord.minSlope
    print "maxSlope      :", newRecord.maxSlope
    print "unused1       :", newRecord.unused1
    print "waterDistance :", newRecord.waterDistance
    print "unused2       :", newRecord.unused2
    print "waterOp       :", newRecord.waterOp
    print "posRange      :", newRecord.posRange
    print "heightRange   :", newRecord.heightRange
    print "colorRange    :", newRecord.colorRange
    print "wavePeriod    :", newRecord.wavePeriod
    print "flags         :", newRecord.flags
    print "unused3       :", newRecord.unused3
        
    print "GRAS:CopyAsOverride Test"
    for record in Current[0].GRAS:
        record.CopyAsOverride(newMod)

    print "GRAS:CopyAsNew Test"
    for record in Current[0].GRAS:
        record.CopyAsNew(newMod)

    print "GRAS:Save Test - TestGRAS.esp"
    newMod.safeSave()
    print "GRAS:Finished testing"


def TestTREE():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestTREE.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.TREE:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "modPath      :", record.modPath
        print "modb         :", record.modb
        print "modt_p       :", record.modt_p
        print "iconPath     :", record.iconPath
        print "speedTree    :", record.speedTree
        print "curvature    :", record.curvature
        print "minAngle     :", record.minAngle
        print "maxAngle     :", record.maxAngle
        print "branchDim    :", record.branchDim
        print "leafDim      :", record.leafDim
        print "shadowRadius :", record.shadowRadius
        print "rockSpeed    :", record.rockSpeed
        print "rustleSpeed  :", record.rustleSpeed  
        print "widthBill    :", record.widthBill
        print "heightBill   :", record.heightBill
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
        break

    print "TREE:Create Record Test"
    newRecord = newMod.createTREERecord()
    print "TREE:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "TREEWarTest"

    newRecord.modPath = r"TREE\path\test.nif"
    newRecord.modb = 1.3
    newRecord.modt_p = [0xFF, 0x00, 0xFE]
    newRecord.iconPath = r"TREE\path\test.dds"
    newRecord.speedTree = [1, 12, 15, 20303]
    newRecord.curvature = 1.4
    newRecord.minAngle = 1.5
    newRecord.maxAngle = 1.6
    newRecord.branchDim = 1.7
    newRecord.leafDim = 1.8
    newRecord.shadowRadius = 12
    newRecord.rockSpeed = 1.9
    newRecord.rustleSpeed = 2.0
    newRecord.widthBill = 2.1
    newRecord.heightBill = 2.2

    print "TREE:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "modPath      :", newRecord.modPath
    print "modb         :", newRecord.modb
    print "modt_p       :", newRecord.modt_p
    print "iconPath     :", newRecord.iconPath
    print "speedTree    :", newRecord.speedTree
    print "curvature    :", newRecord.curvature
    print "minAngle     :", newRecord.minAngle
    print "maxAngle     :", newRecord.maxAngle
    print "branchDim    :", newRecord.branchDim
    print "leafDim      :", newRecord.leafDim
    print "shadowRadius :", newRecord.shadowRadius
    print "rockSpeed    :", newRecord.rockSpeed
    print "rustleSpeed  :", newRecord.rustleSpeed  
    print "widthBill    :", newRecord.widthBill
    print "heightBill   :", newRecord.heightBill
    
    print "TREE:CopyAsOverride Test"
    for record in Current[0].TREE:
        record.CopyAsOverride(newMod)

    print "TREE:CopyAsNew Test"
    for record in Current[0].TREE:
        record.CopyAsNew(newMod)

    print "TREE:Save Test - TestTREE.esp"
    newMod.safeSave()
    print "TREE:Finished testing"


def TestFLOR():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestFLOR.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.FLOR:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full       :", record.full
        print "modPath    :", record.modPath
        print "modb       :", record.modb
        print "modt_p     :", record.modt_p
        print "script     :", record.script
        print "ingredient :", record.ingredient
        print "spring     :", record.spring
        print "summer     :", record.summer
        print "fall       :", record.fall
        print "winter     :", record.winter
        break

    print "FLOR:Create Record Test"
    newRecord = newMod.createFLORRecord()
    print "FLOR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "FLORWarTest"

    newRecord.full = "Fancy FLOR"
    newRecord.modPath = r"GRAS\path\test.nif"
    newRecord.modb = 1.5
    newRecord.modt_p = [0xFF, 0x00, 0xFE]
    newRecord.script = 7
    newRecord.ingredient = 15
    newRecord.spring = 25
    newRecord.summer = 35
    newRecord.fall = 45
    newRecord.winter = 55

    print "FLOR:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "full       :", newRecord.full
    print "modPath    :", newRecord.modPath
    print "modb       :", newRecord.modb
    print "modt_p     :", newRecord.modt_p
    print "script     :", newRecord.script
    print "ingredient :", newRecord.ingredient
    print "spring     :", newRecord.spring
    print "summer     :", newRecord.summer
    print "fall       :", newRecord.fall
    print "winter     :", newRecord.winter
    print "FLOR:CopyAsOverride Test"
    for record in Current[0].FLOR:
        record.CopyAsOverride(newMod)

    print "FLOR:CopyAsNew Test"
    for record in Current[0].FLOR:
        record.CopyAsNew(newMod)

    print "FLOR:Save Test - TestFLOR.esp"
    newMod.safeSave()
    print "FLOR:Finished testing"


def TestFURN():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestFURN.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.FURN:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "script  :", record.script
        print "flags   :", record.flags
        break

    print "FURN:Create Record Test"
    newRecord = newMod.createFURNRecord()
    print "FURN:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "FURNWarTest"
    print "full..."
    newRecord.full = "Fancy FURN"

    print "modPath..."
    newRecord.modPath = r"FURN\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.26
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    newRecord.script = 7
    newRecord.flags = 1
    
    print "FURN:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "script  :", newRecord.script
    print "flags   :", newRecord.flags
    
    print "FURN:CopyAsOverride Test"
    for record in Current[0].FURN:
        record.CopyAsOverride(newMod)

    print "FURN:CopyAsNew Test"
    for record in Current[0].FURN:
        record.CopyAsNew(newMod)

    print "FURN:Save Test - TestFURN.esp"
    newMod.safeSave()
    print "FURN:Finished testing"


def TestWEAP():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestWEAP.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.WEAP:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full          :", record.full
        print "modPath       :", record.modPath
        print "modb          :", record.modb
        print "modt_p        :", record.modt_p
        print "iconPath      :", record.iconPath
        print "script        : %08X" % record.script
        print "enchantment   : %08X" % record.enchantment
        print "enchantPoints :", record.enchantPoints                    
        print "weaponType    :", record.weaponType
        print "speed         :", record.speed
        print "reach         :", record.reach
        print "flags         :", record.flags
        print "value         :", record.value
        print "health        :", record.health
        print "weight        :", record.weight
        print "damage        :", record.damage
        
        break

    print "WEAP:Create Record Test"
    newRecord = newMod.createWEAPRecord()
    print "WEAP:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WEAPWarTest"

    newRecord.full = "Fancy WEAP"

    print "modPath..."
    newRecord.modPath = r"WEAP\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.46
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "iconPath..."
    newRecord.iconPath = r"WEAP\path\test.dds"
    newRecord.script = 7
    
    newRecord.enchantment = 15
    newRecord.enchantPoints = 255                    
    newRecord.weaponType = 1
    newRecord.speed = 1.2
    newRecord.reach = 1.3
    newRecord.flags = 1
    newRecord.value = 151
    newRecord.health = 362
    newRecord.weight = 32.5
    newRecord.damage = 15

    print "WEAP:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full          :", newRecord.full
    print "modPath       :", newRecord.modPath
    print "modb          :", newRecord.modb
    print "modt_p        :", newRecord.modt_p
    print "iconPath      :", newRecord.iconPath
    print "script        : %08X" % newRecord.script
    print "enchantment   : %08X" % newRecord.enchantment
    print "enchantPoints :", newRecord.enchantPoints                    
    print "weaponType    :", newRecord.weaponType
    print "speed         :", newRecord.speed
    print "reach         :", newRecord.reach
    print "flags         :", newRecord.flags
    print "value         :", newRecord.value
    print "health        :", newRecord.health
    print "weight        :", newRecord.weight
    print "damage        :", newRecord.damage
    
    print "WEAP:CopyAsOverride Test"
    for record in Current[0].WEAP:
        record.CopyAsOverride(newMod)

    print "WEAP:CopyAsNew Test"
    for record in Current[0].WEAP:
        record.CopyAsNew(newMod)

    print "WEAP:Save Test - TestWEAP.esp"
    newMod.safeSave()
    print "WEAP:Finished testing"


def TestAMMO():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestAMMO.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.AMMO:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full          :", record.full
        print "modPath       :", record.modPath
        print "modb          :", record.modb
        print "modt_p        :", record.modt_p
        print "iconPath      :", record.iconPath
        print "enchantment   : %08X" % record.enchantment
        print "enchantPoints :", record.enchantPoints     
        print "speed         :", record.speed  
        print "flags         :", record.flags
        print "unused1       :", record.unused1
        print "value         :", record.value
        print "weight        :", record.weight
        print "damage        :", record.damage
        break

    print "AMMO:Create Record Test"
    newRecord = newMod.createAMMORecord()
    print "AMMO:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "AMMOWarTest"

    newRecord.full = "Fancy AMMO"

    print "modPath..."
    newRecord.modPath = r"AMMO\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.46
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "iconPath..."
    newRecord.iconPath = r"AMMO\path\test.dds"
    
    newRecord.enchantment = 15
    newRecord.enchantPoints = 255                    
    newRecord.speed = 1.2
    newRecord.flags = 1
    newRecord.unused1 = [0x08, 0x25, 0xFF]
    newRecord.value = 151
    newRecord.weight = 32.5
    newRecord.damage = 15
    
    print "AMMO:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full          :", newRecord.full
    print "modPath       :", newRecord.modPath
    print "modb          :", newRecord.modb
    print "modt_p        :", newRecord.modt_p
    print "iconPath      :", newRecord.iconPath
    print "enchantment   : %08X" % newRecord.enchantment
    print "enchantPoints :", newRecord.enchantPoints     
    print "speed         :", newRecord.speed  
    print "flags         :", newRecord.flags
    print "unused1       :", newRecord.unused1
    print "value         :", newRecord.value
    print "weight        :", newRecord.weight
    print "damage        :", newRecord.damage
    
    print "AMMO:CopyAsOverride Test"
    for record in Current[0].AMMO:
        record.CopyAsOverride(newMod)

    print "AMMO:CopyAsNew Test"
    for record in Current[0].AMMO:
        record.CopyAsNew(newMod)

    print "AMMO:Save Test - TestAMMO.esp"
    newMod.safeSave()
    print "AMMO:Finished testing"


def TestNPC_():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestNPC_.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.NPC_:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full       :", record.full
        print "modPath    :", record.modPath
        print "modb       :", record.modb
        print "modt_p     :", record.modt_p
        print "flags      :", record.flags
        print "baseSpell  :", record.baseSpell
        print "fatigue    :", record.fatigue
        print "barterGold :", record.barterGold
        print "level      :", record.level
        print "calcMin    :", record.calcMin
        print "calcMax    :", record.calcMax
        print "factions"
        for faction in record.factions:
             print "  %i: Faction: %08X, Rank: %i, Unused1:" % (faction._listIndex, faction.faction, faction.rank), faction.unused1
        print "deathItem : %08X" % record.deathItem
        print "race      : %08X" % record.race
        
        print "spells    :"
        for spell in record.spells:
            print "  %08X" % spell
            
        print "script    : %08X" % record.script
        print "items     :"
        for item in record.items:
            print "  %i: item: %08X, count: %i" % (item._listIndex, item.item, item.count)
        print "aggression     :", record.aggression
        print "confidence     :", record.confidence
        print "energyLevel    :", record.energyLevel
        print "responsibility :", record.responsibility
        print "services       :", record.services
        print "trainSkill     :", record.trainSkill
        print "trainLevel     :", record.trainLevel
        print "unused1        :", record.unused1

        print "aiPackages     :"
        for package in record.aiPackages:
            print "  %08X" % package

        print "animations     :"
        for animation in record.animations:
            print "  ", animation
        
        print "iclass         : %08X" % record.iclass
        print "armorer      :", record.armorer
        print "athletics    :", record.athletics
        print "blade        :", record.blade
        print "block        :", record.block
        print "blunt        :", record.blunt
        print "h2h          :", record.h2h
        print "heavyArmor   :", record.heavyArmor
        print "alchemy      :", record.alchemy
        print "alteration   :", record.alteration
        print "conjuration  :", record.conjuration
        print "destruction  :", record.destruction
        print "illusion     :", record.illusion
        print "mysticism    :", record.mysticism
        print "restoration  :", record.restoration
        print "acrobatics   :", record.acrobatics
        print "lightArmor   :", record.lightArmor
        print "marksman     :", record.marksman
        print "mercantile   :", record.mercantile
        print "security     :", record.security
        print "sneak        :", record.sneak
        print "speechcraft  :", record.speechcraft
        print "health       :", record.health
        print "unused2      :", record.unused2
        print "strength     :", record.strength
        print "intelligence :", record.intelligence
        print "willpower    :", record.willpower
        print "agility      :", record.agility
        print "speed        :", record.speed
        print "endurance    :", record.endurance
        print "personality  :", record.personality
        print "luck         :", record.luck
        print "hair        : %08X" % record.hair
        print "hairLength  :", record.hairLength
        print "eye         : %08X" % record.eye
        print "hairRed     :", record.hairRed
        print "hairGreen   :", record.hairGreen
        print "hairBlue    :", record.hairBlue
        print "unused3     :", record.unused3
        print "combatStyle : %08X" % record.combatStyle
        print "fggs_p :", record.fggs_p
        print "fgga_p :", record.fgga_p
        print "fgts_p :", record.fgts_p
        print "fnam :", record.fnam

        break

    print "NPC_:Create Record Test"
    newRecord = newMod.createNPC_Record()
    print "NPC_:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "NPC_WarTest"

    newRecord.full = "Fancy NPC_"

    print "modPath..."
    newRecord.modPath = r"NPC_\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.76
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    newRecord.flags = 1
    newRecord.baseSpell = 10
    newRecord.fatigue = 20
    newRecord.barterGold = 30
    newRecord.level = 40
    newRecord.calcMin = 50
    newRecord.calcMax = 60

    print "factions..."
    newFaction = newRecord.newFactionsElement()
    newFaction.faction = 1
    newFaction.rank = 2
    newFaction.unused1 = [1,2,3]
    
    newFaction = newRecord.newFactionsElement()
    newFaction.faction = 3
    newFaction.rank = 4
    newFaction.unused1 = [4,5,6]
    
    newFaction = newRecord.newFactionsElement()
    newFaction.faction = 5
    newFaction.rank = 6
    newFaction.unused1 = [7,8,9]
    
    newFaction = newRecord.newFactionsElement()
    newFaction.faction = 7
    newFaction.rank = 8
    newFaction.unused1 = [10,11,12]
    newRecord.factions =[newRecord.factions[3], newRecord.factions[2], newRecord.factions[0]]

    newRecord.deathItem = 14
    newRecord.race = 15
    newRecord.spells = [0xFF000121, 0xFE000222]
    newRecord.script = 7
    
    item = newRecord.newItemsElement()
    item.item = 0x0100000A
    item.count = 50
    item = newRecord.newItemsElement()
    item.item = 0x0000000B
    item.count = 1
    item = newRecord.newItemsElement()
    item.item = 0x0000000C
    item.count = 2
    item = newRecord.newItemsElement()
    item.item = 0x0000000D
    item.count = 3
    newRecord.items = [newRecord.items[3], newRecord.items[2], newRecord.items[0]]

    newRecord.aggression = 1
    newRecord.confidence = 2
    newRecord.energyLevel = 3
    newRecord.responsibility = 4
    newRecord.services = 1
    newRecord.trainSkill = 5
    newRecord.trainLevel = 6
    newRecord.unused1 = [1,2]
    
    newRecord.aiPackages = [0xFF000223, 0xFE000324]
    
    newRecord.animations = [r"NPC_\hay2\anim1.nif", r"NPC_\hay2\anim2.nif", r"NPC_\hay2\anim3.nif", r"NPC_\hay2\anim4.nif"]
    
    newRecord.iclass = 16
    newRecord.armorer = 7
    newRecord.athletics = 8
    newRecord.blade = 9
    newRecord.block = 10
    newRecord.blunt = 11
    newRecord.h2h = 12
    newRecord.heavyArmor = 13
    newRecord.alchemy = 14
    newRecord.alteration = 15
    newRecord.conjuration = 16
    newRecord.destruction = 17
    newRecord.illusion = 18
    newRecord.mysticism = 19
    newRecord.restoration = 20
    newRecord.acrobatics = 21
    newRecord.lightArmor = 22
    newRecord.marksman = 23
    newRecord.mercantile = 24
    newRecord.security = 25
    newRecord.sneak = 26
    newRecord.speechcraft = 27
    newRecord.health = 28
    newRecord.unused2 = [3,4]
    newRecord.strength = 29
    newRecord.intelligence = 30
    newRecord.willpower = 31
    newRecord.agility = 32
    newRecord.speed = 33
    newRecord.endurance = 34
    newRecord.personality = 35
    newRecord.luck = 36
    newRecord.hair = 9
    newRecord.hairLength = 1.1
    newRecord.eye = 10
    newRecord.hairRed = 1
    newRecord.hairGreen = 2
    newRecord.hairBlue = 3
    newRecord.unused3 = [1]
    newRecord.combatStyle = 11
    newRecord.fggs_p = [4] * 200
    newRecord.fgga_p = [5] * 120
    newRecord.fgts_p = [6] * 200
    newRecord.fnam = 40

    print "NPC_:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full       :", newRecord.full
    print "modPath    :", newRecord.modPath
    print "modb       :", newRecord.modb
    print "modt_p     :", newRecord.modt_p
    print "flags      :", newRecord.flags
    print "baseSpell  :", newRecord.baseSpell
    print "fatigue    :", newRecord.fatigue
    print "barterGold :", newRecord.barterGold
    print "level      :", newRecord.level
    print "calcMin    :", newRecord.calcMin
    print "calcMax    :", newRecord.calcMax
    print "factions"
    for faction in newRecord.factions:
         print "  %i: Faction: %08X, Rank: %i, Unused1:" % (faction._listIndex, faction.faction, faction.rank), faction.unused1
    print "deathItem : %08X" % newRecord.deathItem
    print "race      : %08X" % newRecord.race
    
    print "spells    :"
    for spell in newRecord.spells:
        print "  %08X" % spell
        
    print "script    : %08X" % newRecord.script
    print "items     :"
    for item in newRecord.items:
        print "  %i: item: %08X, count: %i" % (item._listIndex, item.item, item.count)
    print "aggression     :", newRecord.aggression
    print "confidence     :", newRecord.confidence
    print "energyLevel    :", newRecord.energyLevel
    print "responsibility :", newRecord.responsibility
    print "services       :", newRecord.services
    print "trainSkill     :", newRecord.trainSkill
    print "trainLevel     :", newRecord.trainLevel
    print "unused1        :", newRecord.unused1

    print "aiPackages     :"
    for package in newRecord.aiPackages:
        print "  %08X" % package

    print "animations     :"
    for animation in newRecord.animations:
        print "  ", animation
    
    print "iclass         : %08X" % newRecord.iclass
    print "armorer      :", newRecord.armorer
    print "athletics    :", newRecord.athletics
    print "blade        :", newRecord.blade
    print "block        :", newRecord.block
    print "blunt        :", newRecord.blunt
    print "h2h          :", newRecord.h2h
    print "heavyArmor   :", newRecord.heavyArmor
    print "alchemy      :", newRecord.alchemy
    print "alteration   :", newRecord.alteration
    print "conjuration  :", newRecord.conjuration
    print "destruction  :", newRecord.destruction
    print "illusion     :", newRecord.illusion
    print "mysticism    :", newRecord.mysticism
    print "restoration  :", newRecord.restoration
    print "acrobatics   :", newRecord.acrobatics
    print "lightArmor   :", newRecord.lightArmor
    print "marksman     :", newRecord.marksman
    print "mercantile   :", newRecord.mercantile
    print "security     :", newRecord.security
    print "sneak        :", newRecord.sneak
    print "speechcraft  :", newRecord.speechcraft
    print "health       :", newRecord.health
    print "unused2      :", newRecord.unused2
    print "strength     :", newRecord.strength
    print "intelligence :", newRecord.intelligence
    print "willpower    :", newRecord.willpower
    print "agility      :", newRecord.agility
    print "speed        :", newRecord.speed
    print "endurance    :", newRecord.endurance
    print "personality  :", newRecord.personality
    print "luck         :", newRecord.luck
    print "hair        : %08X" % newRecord.hair
    print "hairLength  :", newRecord.hairLength
    print "eye         : %08X" % newRecord.eye
    print "hairRed     :", newRecord.hairRed
    print "hairGreen   :", newRecord.hairGreen
    print "hairBlue    :", newRecord.hairBlue
    print "unused3     :", newRecord.unused3
    print "combatStyle : %08X" % newRecord.combatStyle
    print "fggs_p :", newRecord.fggs_p
    print "fgga_p :", newRecord.fgga_p
    print "fgts_p :", newRecord.fgts_p
    print "fnam :", newRecord.fnam    
    print "NPC_:CopyAsOverride Test"
    for record in Current[0].NPC_:
        record.CopyAsOverride(newMod)

    print "NPC_:CopyAsNew Test"
    for record in Current[0].NPC_:
        record.CopyAsNew(newMod)

    print "NPC_:Save Test - TestNPC_.esp"
    newMod.safeSave()
    print "NPC_:Finished testing"


def TestCREA():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCREA.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.CREA:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid
            
        print "full       :", record.full
        print "modPath    :", record.modPath
        print "modb       :", record.modb
        print "modt_p     :", record.modt_p

        print "spells"
        for spell in record.spells:
            print "  %08X" % spell
            
        print "bodyParts"
        for bodyPart in record.bodyParts:
            print "  ", bodyPart

        print "nift_p     :", record.nift_p
            
        print "flags      :", record.flags
        print "baseSpell  :", record.baseSpell
        print "fatigue    :", record.fatigue
        print "barterGold :", record.barterGold
        print "level      :", record.level
        print "calcMin    :", record.calcMin
        print "calcMax    :", record.calcMax
        
        print "factions"
        for faction in record.factions:
             print "  %i: Faction: %08X, Rank: %i, Unused1:" % (faction._listIndex, faction.faction, faction.rank), faction.unused1

        print "deathItem : %08X" % record.deathItem
        print "script    : %08X" % record.script

        print "items"
        for item in record.items:
            print "  %i: item: %08X, count: %i" % (item._listIndex, item.item, item.count)

        print "aggression     :", record.aggression
        print "confidence     :", record.confidence
        print "energyLevel    :", record.energyLevel
        print "responsibility :", record.responsibility
        print "services       :", record.services
        print "trainSkill     :", record.trainSkill
        print "trainLevel     :", record.trainLevel
        print "unused1        :", record.unused1

        print "aiPackages     :"
        for package in record.aiPackages:
            print "  %08X" % package

        print "animations     :"
        for animation in record.animations:
            print "  ", animation
            
        print "creatureType :", record.creatureType
        print "combat       :", record.combat
        print "magic        :", record.magic
        print "stealth      :", record.stealth
        print "soul         :", record.soul
        print "unused2      :", record.unused2
        print "health       :", record.health
        print "unused3      :", record.unused3
        print "attackDamage :", record.attackDamage
        print "strength     :", record.strength
        print "intelligence :", record.intelligence
        print "willpower    :", record.willpower
        print "agility      :", record.agility
        print "speed        :", record.speed
        print "endurance    :", record.endurance
        print "personality  :", record.personality
        print "luck         :", record.luck
        
        print "attackReach  :", record.attackReach
        print "combatStyle  : %08X" % record.combatStyle
        print "turningSpeed :", record.turningSpeed
        print "baseScale    :", record.baseScale
        print "footWeight   :", record.footWeight
        print "inheritsSoundsFrom  : %08X" % record.inheritsSoundsFrom
        print "bloodSprayPath      :", record.bloodSprayPath
        print "bloodDecalPath      :", record.bloodDecalPath
        
        print "sounds"
        for sound in record.sounds:
            print "  %i: type: %u, sound: %08X, chance:%i" % (sound._listIndex, sound.type, sound.sound, sound.chance)
        break

    print "CREA:Create Record Test"
    newRecord = newMod.createCREARecord()
    print "CREA:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CREAWarTest"

    newRecord.full = "Fancy CREA"

    print "modPath..."
    newRecord.modPath = r"CREA\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.76
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newRecord.spells = [0xFF000121, 0xFE000222]
    newRecord.bodyParts = [r"CREA\hay2\body1.nif", r"CREA\hay2\body2.nif", r"CREA\hay2\body3.nif", r"CREA\hay2\body4.nif"]
    
    newRecord.nift_p = [0x00, 0xFE, 0xFE]
    
    newRecord.flags = 1
    newRecord.baseSpell = 10
    newRecord.fatigue = 20
    newRecord.barterGold = 30
    newRecord.level = 40
    newRecord.calcMin = 50
    newRecord.calcMax = 60

    print "factions..."
    newFaction = newRecord.newFactionsElement()
    newFaction.faction = 1
    newFaction.rank = 2
    newFaction.unused1 = [1,2,3]
    
    newFaction = newRecord.newFactionsElement()
    newFaction.faction = 3
    newFaction.rank = 4
    newFaction.unused1 = [4,5,6]
    
    newFaction = newRecord.newFactionsElement()
    newFaction.faction = 5
    newFaction.rank = 6
    newFaction.unused1 = [7,8,9]
    
    newFaction = newRecord.newFactionsElement()
    newFaction.faction = 7
    newFaction.rank = 8
    newFaction.unused1 = [10,11,12]
    newRecord.factions =[newRecord.factions[3], newRecord.factions[2], newRecord.factions[0]]

    newRecord.deathItem = 14
    newRecord.script = 7
    
    item = newRecord.newItemsElement()
    item.item = 0x0100000A
    item.count = 50
    item = newRecord.newItemsElement()
    item.item = 0x0000000B
    item.count = 1
    item = newRecord.newItemsElement()
    item.item = 0x0000000C
    item.count = 2
    item = newRecord.newItemsElement()
    item.item = 0x0000000D
    item.count = 3
    newRecord.items = [newRecord.items[3], newRecord.items[2], newRecord.items[0]]

    newRecord.aggression = 1
    newRecord.confidence = 2
    newRecord.energyLevel = 3
    newRecord.responsibility = 4
    newRecord.services = 1
    newRecord.trainSkill = 5
    newRecord.trainLevel = 6
    newRecord.unused1 = [1,2]
    
    newRecord.aiPackages = [0xFF000223, 0xFE000324]
    
    newRecord.animations = [r"CREA\hay2\anim1.nif", r"CREA\hay2\anim2.nif", r"CREA\hay2\anim3.nif", r"CREA\hay2\anim4.nif"]
    
    newRecord.creatureType = 1
    newRecord.combat = 7
    newRecord.magic = 8
    newRecord.stealth = 9
    newRecord.soul = 1
    newRecord.unused2 = [3]
    newRecord.health = 27
    newRecord.unused3 = [4,5]
    newRecord.attackDamage = 28
    newRecord.strength = 29
    newRecord.intelligence = 30
    newRecord.willpower = 31
    newRecord.agility = 32
    newRecord.speed = 33
    newRecord.endurance = 34
    newRecord.personality = 35
    newRecord.luck = 36
    newRecord.attackReach = 10
    newRecord.combatStyle = 11
    newRecord.turningSpeed = 1.1
    newRecord.baseScale = 1.2
    newRecord.footWeight = 1.3
    newRecord.inheritsSoundsFrom = 0x14
    newRecord.bloodSprayPath = r"CREA\bloodSprayPath\anim1.dds"
    newRecord.bloodDecalPath = r"CREA\bloodDecalPath\anim1.dds"

    sound = newRecord.newSoundsElement()
    sound.type = 0
    sound.sound = 0x0100000A
    sound.chance = 0
    sound = newRecord.newSoundsElement()
    sound.type = 1
    sound.sound = 0x0000000B
    sound.chance = 1
    sound = newRecord.newSoundsElement()
    sound.type = 2
    sound.sound = 0x0000000C
    sound.chance = 2
    sound = newRecord.newSoundsElement()
    sound.type = 3
    sound.sound = 0x0000000D
    sound.chance = 3
    newRecord.sounds = [newRecord.sounds[3], newRecord.sounds[2], newRecord.sounds[0]]
    
    print "CREA:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full       :", newRecord.full
    print "modPath    :", newRecord.modPath
    print "modb       :", newRecord.modb
    print "modt_p     :", newRecord.modt_p

    print "spells"
    for spell in newRecord.spells:
        print "  %08X" % spell
        
    print "bodyParts"
    for bodyPart in newRecord.bodyParts:
        print "  ", bodyPart

    print "nift_p     :", newRecord.nift_p
        
    print "flags      :", newRecord.flags
    print "baseSpell  :", newRecord.baseSpell
    print "fatigue    :", newRecord.fatigue
    print "barterGold :", newRecord.barterGold
    print "level      :", newRecord.level
    print "calcMin    :", newRecord.calcMin
    print "calcMax    :", newRecord.calcMax
    
    print "factions"
    for faction in newRecord.factions:
         print "  %i: Faction: %08X, Rank: %i, Unused1:" % (faction._listIndex, faction.faction, faction.rank), faction.unused1

    print "deathItem : %08X" % newRecord.deathItem
    print "script    : %08X" % newRecord.script

    print "items"
    for item in newRecord.items:
        print "  %i: item: %08X, count: %i" % (item._listIndex, item.item, item.count)

    print "aggression     :", newRecord.aggression
    print "confidence     :", newRecord.confidence
    print "energyLevel    :", newRecord.energyLevel
    print "responsibility :", newRecord.responsibility
    print "services       :", newRecord.services
    print "trainSkill     :", newRecord.trainSkill
    print "trainLevel     :", newRecord.trainLevel
    print "unused1        :", newRecord.unused1

    print "aiPackages     :"
    for package in newRecord.aiPackages:
        print "  %08X" % package

    print "animations     :"
    for animation in newRecord.animations:
        print "  ", animation
        
    print "creatureType :", newRecord.creatureType
    print "combat       :", newRecord.combat
    print "magic        :", newRecord.magic
    print "stealth      :", newRecord.stealth
    print "soul         :", newRecord.soul
    print "unused2      :", newRecord.unused2
    print "health       :", newRecord.health
    print "unused3      :", newRecord.unused3
    print "attackDamage :", newRecord.attackDamage
    print "strength     :", newRecord.strength
    print "intelligence :", newRecord.intelligence
    print "willpower    :", newRecord.willpower
    print "agility      :", newRecord.agility
    print "speed        :", newRecord.speed
    print "endurance    :", newRecord.endurance
    print "personality  :", newRecord.personality
    print "luck         :", newRecord.luck
    
    print "attackReach  :", newRecord.attackReach
    print "combatStyle  : %08X" % newRecord.combatStyle
    print "turningSpeed :", newRecord.turningSpeed
    print "baseScale    :", newRecord.baseScale
    print "footWeight   :", newRecord.footWeight
    print "inheritsSoundsFrom  : %08X" % newRecord.inheritsSoundsFrom
    print "bloodSprayPath      :", newRecord.bloodSprayPath
    print "bloodDecalPath      :", newRecord.bloodDecalPath
    
    print "sounds"
    for sound in newRecord.sounds:
        print "  %i: type: %u, sound: %08X, chance:%i" % (sound._listIndex, sound.type, sound.sound, sound.chance)
    print "CREA:CopyAsOverride Test"
    for record in Current[0].CREA:
        record.CopyAsOverride(newMod)

    print "CREA:CopyAsNew Test"
    for record in Current[0].CREA:
        record.CopyAsNew(newMod)

    print "CREA:Save Test - TestCREA.esp"
    newMod.safeSave()
    print "CREA:Finished testing"


def TestLVLC():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLVLC.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.LVLC:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "chanceNone :", record.chanceNone
        print "flags      :", record.flags
        print "script     : %08X" % record.script
        print "template   : %08X" % record.template
        print "entries"
        for entry in record.entries:
            print
            print "  level   :", entry.level
            print "  unused1 :", entry.unused1
            print "  listId  : %08X" % entry.listId
            print "  count   :", entry.count
            print "  unused2 :", entry.unused2
        break

    print "LVLC:Create Record Test"
    newRecord = newMod.createLVLCRecord()
    print "LVLC:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "LVLCWarTest"

    newRecord.chanceNone = 20
    newRecord.flags = 1
    newRecord.script = 7
    newRecord.template = 0x14

    entry = newRecord.newEntriesElement()
    entry.level = 1
    entry.unused1 = [0x14, 0xFF]
    entry.listId = 0x0100000A
    entry.count = 2
    entry.unused2 = [0x15, 0xFF]
    entry = newRecord.newEntriesElement()
    entry.level = 3
    entry.unused1 = [0x16, 0xFF]
    entry.listId = 0x0000000B
    entry.count = 4
    entry.unused2 = [0x17, 0xFF]
    entry = newRecord.newEntriesElement()
    entry.level = 5
    entry.unused1 = [0x18, 0xFF]
    entry.listId = 0x0000000C
    entry.count = 6
    entry.unused2 = [0x19, 0xFF]
    entry = newRecord.newEntriesElement()
    entry.level = 7
    entry.unused1 = [0x20, 0xFF]
    entry.listId = 0x0000000D
    entry.count = 8
    entry.unused2 = [0x21, 0xFF]
    newRecord.entries = [newRecord.entries[3], newRecord.entries[2], newRecord.entries[0]]


    print "LVLC:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "chanceNone :", newRecord.chanceNone
    print "flags      :", newRecord.flags
    print "script     : %08X" % newRecord.script
    print "template   : %08X" % newRecord.template
    print "entries"
    for entry in newRecord.entries:
        print
        print "  level   :", entry.level
        print "  unused1 :", entry.unused1
        print "  listId  : %08X" % entry.listId
        print "  count   :", entry.count
        print "  unused2 :", entry.unused2
            
    print "LVLC:CopyAsOverride Test"
    for record in Current[0].LVLC:
        record.CopyAsOverride(newMod)

    print "LVLC:CopyAsNew Test"
    for record in Current[0].LVLC:
        record.CopyAsNew(newMod)

    print "LVLC:Save Test - TestLVLC.esp"
    newMod.safeSave()
    print "LVLC:Finished testing"


def TestSLGM():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSLGM.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.SLGM:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "iconPath:", record.iconPath
        print "script  : %08X" % record.script
        print "value   :", record.value
        print "weight  :", record.weight

        print "soul     :", record.soul
        print "capacity :", record.capacity
        break

    print "SLGM:Create Record Test"
    newRecord = newMod.createSLGMRecord()
    print "SLGM:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SLGMWarTest"
    print "full..."
    newRecord.full = "Fancy SLGM"

    print "modPath..."
    newRecord.modPath = r"SLGM\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "iconPath..."
    newRecord.iconPath = r"SLGM\path\test.dds"
    newRecord.script = 7
    newRecord.value = 150
    newRecord.weight = 3.56

    newRecord.soul = 1
    newRecord.capacity = 50
    
    print "SLGM:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath:", newRecord.iconPath
    print "script  : %08X" % newRecord.script
    print "value   :", newRecord.value
    print "weight  :", newRecord.weight

    print "soul     :", newRecord.soul
    print "capacity :", newRecord.capacity
    
    print "SLGM:CopyAsOverride Test"
    for record in Current[0].SLGM:
        record.CopyAsOverride(newMod)

    print "SLGM:CopyAsNew Test"
    for record in Current[0].SLGM:
        record.CopyAsNew(newMod)

    print "SLGM:Save Test - TestSLGM.esp"
    newMod.safeSave()
    print "SLGM:Finished testing"


def TestKEYM():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestKEYM.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.KEYM:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "iconPath:", record.iconPath
        print "script  : %08X" % record.script
        print "value   :", record.value
        print "weight  :", record.weight
        break

    print "KEYM:Create Record Test"
    newRecord = newMod.createKEYMRecord()
    print "KEYM:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "KEYMWarTest"
    print "full..."
    newRecord.full = "Fancy KEYM"

    print "modPath..."
    newRecord.modPath = r"KEYM\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "iconPath..."
    newRecord.iconPath = r"KEYM\path\test.dds"
    newRecord.script = 7
    newRecord.value = 150
    newRecord.weight = 3.56

    print "KEYM:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p
    print "iconPath:", newRecord.iconPath
    print "script  :", newRecord.script
    print "value   :", newRecord.value
    print "weight  :", newRecord.weight
    
    print "KEYM:CopyAsOverride Test"
    for record in Current[0].KEYM:
        record.CopyAsOverride(newMod)

    print "KEYM:CopyAsNew Test"
    for record in Current[0].KEYM:
        record.CopyAsNew(newMod)

    print "KEYM:Save Test - TestKEYM.esp"
    newMod.safeSave()
    print "KEYM:Finished testing"

def TestALCH():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestALCH.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.ALCH:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "iconPath:", record.iconPath
        print "script  : %08X" % record.script
        print "weight  :", record.weight
        print "value   :", record.value
        print "flags   :", record.flags
        
        print "unused1 :", record.unused1
        
        print "effects :"
        for effect in record.effects:
            print "  name0      :", effect.name0
            print "  name       :", effect.name
            print "  magnitude  :", effect.magnitude
            print "  area       :", effect.area
            print "  duration   :", effect.duration
            print "  recipient  :", effect.recipient
            print "  actorValue :", effect.actorValue
            print "  script     : %08X" % effect.script
            print "  school     :", effect.school
            print "  visual     :", effect.visual
            print "  flags      :", effect.flags
            print "  unused1    :", effect.unused1
            print "  full       :", effect.full
            print
        break

    print "ALCH:Create Record Test"
    newRecord = newMod.createALCHRecord()
    print "ALCH:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "ALCHWarTest"
    print "full..."
    newRecord.full = "Fancy ALCH"

    print "modPath..."
    newRecord.modPath = r"ALCH\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "iconPath..."
    newRecord.iconPath = r"ALCH\path\test.dds"
    newRecord.script = 7
    newRecord.weight = 3.56
    newRecord.value = 150

    newRecord.flags = 1
    
    newRecord.unused1 = [0x00, 0xFE, 0xFD]

    newEffect = newRecord.newEffectsElement()
    newEffect.name0 = 0x52474E49
    newEffect.name = 0x53414C43
    newEffect.magnitude = 1
    newEffect.area = 2
    newEffect.duration = 3
    newEffect.recipient = 4
    newEffect.actorValue = 5
    newEffect.script = 0xFF000007
    newEffect.school = 324
    newEffect.visual = 0x52474E49
    newEffect.flags = 16
    newEffect.unused1 = [3,4,5]
    newEffect.full = "ALCH?"

    newEffect = newRecord.newEffectsElement()
    newEffect.name0 = 0x52474E49
    newEffect.name = 0x52474E49
    newEffect.magnitude = 6
    newEffect.area = 7
    newEffect.duration = 8
    newEffect.recipient = 9
    newEffect.actorValue = 10
    newEffect.script = 0xFF00000A
    newEffect.school = 11
    newEffect.visual = 0x4C455053
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "ALCH??"
    
    print "ALCH:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath:", newRecord.iconPath
    print "script  : %08X" % newRecord.script
    print "weight  :", newRecord.weight
    print "value   :", newRecord.value
    print "flags   :", newRecord.flags
    
    print "unused1 :", newRecord.unused1
    
    print "effects :"
    for effect in newRecord.effects:
        print "  name0      :", effect.name0
        print "  name       :", effect.name
        print "  magnitude  :", effect.magnitude
        print "  area       :", effect.area
        print "  duration   :", effect.duration
        print "  recipient  :", effect.recipient
        print "  actorValue :", effect.actorValue
        print "  script     : %08X" % effect.script
        print "  school     :", effect.school
        print "  visual     :", effect.visual
        print "  flags      :", effect.flags
        print "  unused1    :", effect.unused1
        print "  full       :", effect.full
        print    
    print "ALCH:CopyAsOverride Test"
    for record in Current[0].ALCH:
        record.CopyAsOverride(newMod)

    print "ALCH:CopyAsNew Test"
    for record in Current[0].ALCH:
        record.CopyAsNew(newMod)

    print "ALCH:Save Test - TestALCH.esp"
    newMod.safeSave()
    print "ALCH:Finished testing"

def TestSBSP():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSBSP.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.SBSP:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        break

    print "SBSP:Create Record Test"
    newRecord = newMod.createSBSPRecord()
    print "SBSP:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SBSPWarTest"


    print "SBSP:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    
    print "SBSP:CopyAsOverride Test"
    for record in Current[0].SBSP:
        record.CopyAsOverride(newMod)

    print "SBSP:CopyAsNew Test"
    for record in Current[0].SBSP:
        record.CopyAsNew(newMod)

    print "SBSP:Save Test - TestSBSP.esp"
    newMod.safeSave()
    print "SBSP:Finished testing"


def TestSGST():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSGST.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.SGST:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full    :", record.full
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "iconPath:", record.iconPath
        print "script  : %08X" % record.script

        print "effects :"
        for effect in record.effects:
            print "  name0      :", effect.name0
            print "  name       :", effect.name
            print "  magnitude  :", effect.magnitude
            print "  area       :", effect.area
            print "  duration   :", effect.duration
            print "  recipient  :", effect.recipient
            print "  actorValue :", effect.actorValue
            print "  script     : %08X" % effect.script
            print "  school     :", effect.school
            print "  visual     :", effect.visual
            print "  flags      :", effect.flags
            print "  unused1    :", effect.unused1
            print "  full       :", effect.full
            print
            
        print "uses   :", record.uses
        print "value   :", record.value
        print "weight  :", record.weight
        

        break

    print "SGST:Create Record Test"
    newRecord = newMod.createSGSTRecord()
    print "SGST:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SGSTWarTest"
    print "full..."
    newRecord.full = "Fancy SGST"

    print "modPath..."
    newRecord.modPath = r"SGST\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    
    print "iconPath..."
    newRecord.iconPath = r"SGST\path\test.dds"
    newRecord.script = 7

    newEffect = newRecord.newEffectsElement()
    newEffect.name0 = 0x52474E49
    newEffect.name = 0x52474E49
    newEffect.magnitude = 1
    newEffect.area = 2
    newEffect.duration = 6
    newEffect.recipient = 6
    newEffect.actorValue = 5
    newEffect.script = 0xFF000007
    newEffect.school = 324
    newEffect.visual = 0x52474E49
    newEffect.flags = 16
    newEffect.unused1 = [3,4,5]
    newEffect.full = "SGST?"

    newEffect = newRecord.newEffectsElement()
    newEffect.name0 = 0x52474E49
    newEffect.name = 0x52474E49
    newEffect.magnitude = 6
    newEffect.area = 7
    newEffect.duration = 7
    newEffect.recipient = 9
    newEffect.actorValue = 10
    newEffect.script = 0xFF00000A
    newEffect.school = 11
    newEffect.visual = 0x4C455053
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "SGST??"


    newEffect = newRecord.newEffectsElement()
    newEffect.name0 = 0x52474E49
    newEffect.name = 0x52474E49
    newEffect.magnitude = 6
    newEffect.area = 8
    newEffect.duration = 8
    newEffect.recipient = 9
    newEffect.actorValue = 10
    newEffect.script = 0xFF00000A
    newEffect.school = 11
    newEffect.visual = 0x4C455053
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "SGST???"
    
    newRecord.effects = [newRecord.effects[0], newRecord.effects[2]]
    
    newRecord.uses = 16
    newRecord.value = 150
    newRecord.weight = 3.56

    print "SGST:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath:", newRecord.iconPath
    print "script  : %08X" % newRecord.script

    print "effects :"
    for effect in newRecord.effects:
        print "  name0      :", effect.name0
        print "  name       :", effect.name
        print "  magnitude  :", effect.magnitude
        print "  area       :", effect.area
        print "  duration   :", effect.duration
        print "  recipient  :", effect.recipient
        print "  actorValue :", effect.actorValue
        print "  script     : %08X" % effect.script
        print "  school     :", effect.school
        print "  visual     :", effect.visual
        print "  flags      :", effect.flags
        print "  unused1    :", effect.unused1
        print "  full       :", effect.full
        print
        
    print "uses   :", newRecord.uses
    print "value   :", newRecord.value
    print "weight  :", newRecord.weight
    
    print "SGST:CopyAsOverride Test"
    for record in Current[0].SGST:
        record.CopyAsOverride(newMod)

    print "SGST:CopyAsNew Test"
    for record in Current[0].SGST:
        record.CopyAsNew(newMod)

    print "SGST:Save Test - TestSGST.esp"
    newMod.safeSave()
    print "SGST:Finished testing"


def TestLVLI():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLVLI.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.LVLI:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "chanceNone :", record.chanceNone
        print "flags      :", record.flags
        print "entries"
        for entry in record.entries:
            print
            print "  level   :", entry.level
            print "  unused1 :", entry.unused1
            print "  listId  : %08X" % entry.listId
            print "  count   :", entry.count
            print "  unused2 :", entry.unused2
        print "data_p :", record.data_p
        break

    print "LVLI:Create Record Test"
    newRecord = newMod.createLVLIRecord()
    print "LVLI:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "LVLIWarTest"

    newRecord.chanceNone = 20
    newRecord.flags = 1

    entry = newRecord.newEntriesElement()
    entry.level = 1
    entry.unused1 = [0x14, 0xFF]
    entry.listId = 0x0100000A
    entry.count = 2
    entry.unused2 = [0x15, 0xFF]
    entry = newRecord.newEntriesElement()
    entry.level = 3
    entry.unused1 = [0x16, 0xFF]
    entry.listId = 0x0000000B
    entry.count = 4
    entry.unused2 = [0x17, 0xFF]
    entry = newRecord.newEntriesElement()
    entry.level = 5
    entry.unused1 = [0x18, 0xFF]
    entry.listId = 0x0000000C
    entry.count = 6
    entry.unused2 = [0x19, 0xFF]
    entry = newRecord.newEntriesElement()
    entry.level = 7
    entry.unused1 = [0x20, 0xFF]
    entry.listId = 0x0000000D
    entry.count = 8
    entry.unused2 = [0x21, 0xFF]
    newRecord.entries = [newRecord.entries[3], newRecord.entries[2], newRecord.entries[0]]

    newRecord.data_p = [0xFF] 

    print "LVLI:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "chanceNone :", newRecord.chanceNone
    print "flags      :", newRecord.flags
    print "entries"
    for entry in newRecord.entries:
        print
        print "  level   :", entry.level
        print "  unused1 :", entry.unused1
        print "  listId  : %08X" % entry.listId
        print "  count   :", entry.count
        print "  unused2 :", entry.unused2
    print "data_p :", newRecord.data_p
    print "LVLI:CopyAsOverride Test"
    for record in Current[0].LVLI:
        record.CopyAsOverride(newMod)

    print "LVLI:CopyAsNew Test"
    for record in Current[0].LVLI:
        record.CopyAsNew(newMod)

    print "LVLI:Save Test - TestLVLI.esp"
    newMod.safeSave()
    print "LVLI:Finished testing"


def TestWTHR():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestWTHR.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.WTHR:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "lowerLayer :", record.lowerLayer
        print "upperLayer :", record.upperLayer
        
        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "upperSky.riseRed    :", record.upperSky.riseRed
        print "upperSky.riseGreen  :", record.upperSky.riseGreen
        print "upperSky.riseBlue   :", record.upperSky.riseBlue
        print "upperSky.unused1    :", record.upperSky.unused1
        print "upperSky.dayRed     :", record.upperSky.dayRed
        print "upperSky.dayGreen   :", record.upperSky.dayGreen
        print "upperSky.dayBlue    :", record.upperSky.dayBlue
        print "upperSky.unused2    :", record.upperSky.unused2
        print "upperSky.setRed     :", record.upperSky.setRed
        print "upperSky.setGreen   :", record.upperSky.setGreen
        print "upperSky.setBlue    :", record.upperSky.setBlue
        print "upperSky.unused3    :", record.upperSky.unused3
        print "upperSky.nightRed   :", record.upperSky.nightRed
        print "upperSky.nightGreen :", record.upperSky.nightGreen
        print "upperSky.nightBlue  :", record.upperSky.nightBlue
        print "upperSky.unused4    :", record.upperSky.unused4
        
        print "fog.riseRed    :", record.fog.riseRed
        print "fog.riseGreen  :", record.fog.riseGreen
        print "fog.riseBlue   :", record.fog.riseBlue
        print "fog.unused1    :", record.fog.unused1
        print "fog.dayRed     :", record.fog.dayRed
        print "fog.dayGreen   :", record.fog.dayGreen
        print "fog.dayBlue    :", record.fog.dayBlue
        print "fog.unused2    :", record.fog.unused2
        print "fog.setRed     :", record.fog.setRed
        print "fog.setGreen   :", record.fog.setGreen
        print "fog.setBlue    :", record.fog.setBlue
        print "fog.unused3    :", record.fog.unused3
        print "fog.nightRed   :", record.fog.nightRed
        print "fog.nightGreen :", record.fog.nightGreen
        print "fog.nightBlue  :", record.fog.nightBlue
        print "fog.unused4    :", record.fog.unused4

        print "lowerClouds.riseRed    :", record.lowerClouds.riseRed
        print "lowerClouds.riseGreen  :", record.lowerClouds.riseGreen
        print "lowerClouds.riseBlue   :", record.lowerClouds.riseBlue
        print "lowerClouds.unused1    :", record.lowerClouds.unused1
        print "lowerClouds.dayRed     :", record.lowerClouds.dayRed
        print "lowerClouds.dayGreen   :", record.lowerClouds.dayGreen
        print "lowerClouds.dayBlue    :", record.lowerClouds.dayBlue
        print "lowerClouds.unused2    :", record.lowerClouds.unused2
        print "lowerClouds.setRed     :", record.lowerClouds.setRed
        print "lowerClouds.setGreen   :", record.lowerClouds.setGreen
        print "lowerClouds.setBlue    :", record.lowerClouds.setBlue
        print "lowerClouds.unused3    :", record.lowerClouds.unused3
        print "lowerClouds.nightRed   :", record.lowerClouds.nightRed
        print "lowerClouds.nightGreen :", record.lowerClouds.nightGreen
        print "lowerClouds.nightBlue  :", record.lowerClouds.nightBlue
        print "lowerClouds.unused4    :", record.lowerClouds.unused4
        
        print "ambient.riseRed    :", record.ambient.riseRed
        print "ambient.riseGreen  :", record.ambient.riseGreen
        print "ambient.riseBlue   :", record.ambient.riseBlue
        print "ambient.unused1    :", record.ambient.unused1
        print "ambient.dayRed     :", record.ambient.dayRed
        print "ambient.dayGreen   :", record.ambient.dayGreen
        print "ambient.dayBlue    :", record.ambient.dayBlue
        print "ambient.unused2    :", record.ambient.unused2
        print "ambient.setRed     :", record.ambient.setRed
        print "ambient.setGreen   :", record.ambient.setGreen
        print "ambient.setBlue    :", record.ambient.setBlue
        print "ambient.unused3    :", record.ambient.unused3
        print "ambient.nightRed   :", record.ambient.nightRed
        print "ambient.nightGreen :", record.ambient.nightGreen
        print "ambient.nightBlue  :", record.ambient.nightBlue
        print "ambient.unused4    :", record.ambient.unused4

        print "sunlight.riseRed    :", record.sunlight.riseRed
        print "sunlight.riseGreen  :", record.sunlight.riseGreen
        print "sunlight.riseBlue   :", record.sunlight.riseBlue
        print "sunlight.unused1    :", record.sunlight.unused1
        print "sunlight.dayRed     :", record.sunlight.dayRed
        print "sunlight.dayGreen   :", record.sunlight.dayGreen
        print "sunlight.dayBlue    :", record.sunlight.dayBlue
        print "sunlight.unused2    :", record.sunlight.unused2
        print "sunlight.setRed     :", record.sunlight.setRed
        print "sunlight.setGreen   :", record.sunlight.setGreen
        print "sunlight.setBlue    :", record.sunlight.setBlue
        print "sunlight.unused3    :", record.sunlight.unused3
        print "sunlight.nightRed   :", record.sunlight.nightRed
        print "sunlight.nightGreen :", record.sunlight.nightGreen
        print "sunlight.nightBlue  :", record.sunlight.nightBlue
        print "sunlight.unused4    :", record.sunlight.unused4

        print "sun.riseRed    :", record.sun.riseRed
        print "sun.riseGreen  :", record.sun.riseGreen
        print "sun.riseBlue   :", record.sun.riseBlue
        print "sun.unused1    :", record.sun.unused1
        print "sun.dayRed     :", record.sun.dayRed
        print "sun.dayGreen   :", record.sun.dayGreen
        print "sun.dayBlue    :", record.sun.dayBlue
        print "sun.unused2    :", record.sun.unused2
        print "sun.setRed     :", record.sun.setRed
        print "sun.setGreen   :", record.sun.setGreen
        print "sun.setBlue    :", record.sun.setBlue
        print "sun.unused3    :", record.sun.unused3
        print "sun.nightRed   :", record.sun.nightRed
        print "sun.nightGreen :", record.sun.nightGreen
        print "sun.nightBlue  :", record.sun.nightBlue
        print "sun.unused4    :", record.sun.unused4

        print "stars.riseRed    :", record.stars.riseRed
        print "stars.riseGreen  :", record.stars.riseGreen
        print "stars.riseBlue   :", record.stars.riseBlue
        print "stars.unused1    :", record.stars.unused1
        print "stars.dayRed     :", record.stars.dayRed
        print "stars.dayGreen   :", record.stars.dayGreen
        print "stars.dayBlue    :", record.stars.dayBlue
        print "stars.unused2    :", record.stars.unused2
        print "stars.setRed     :", record.stars.setRed
        print "stars.setGreen   :", record.stars.setGreen
        print "stars.setBlue    :", record.stars.setBlue
        print "stars.unused3    :", record.stars.unused3
        print "stars.nightRed   :", record.stars.nightRed
        print "stars.nightGreen :", record.stars.nightGreen
        print "stars.nightBlue  :", record.stars.nightBlue
        print "stars.unused4    :", record.stars.unused4

        print "lowerSky.riseRed    :", record.lowerSky.riseRed
        print "lowerSky.riseGreen  :", record.lowerSky.riseGreen
        print "lowerSky.riseBlue   :", record.lowerSky.riseBlue
        print "lowerSky.unused1    :", record.lowerSky.unused1
        print "lowerSky.dayRed     :", record.lowerSky.dayRed
        print "lowerSky.dayGreen   :", record.lowerSky.dayGreen
        print "lowerSky.dayBlue    :", record.lowerSky.dayBlue
        print "lowerSky.unused2    :", record.lowerSky.unused2
        print "lowerSky.setRed     :", record.lowerSky.setRed
        print "lowerSky.setGreen   :", record.lowerSky.setGreen
        print "lowerSky.setBlue    :", record.lowerSky.setBlue
        print "lowerSky.unused3    :", record.lowerSky.unused3
        print "lowerSky.nightRed   :", record.lowerSky.nightRed
        print "lowerSky.nightGreen :", record.lowerSky.nightGreen
        print "lowerSky.nightBlue  :", record.lowerSky.nightBlue
        print "lowerSky.unused4    :", record.lowerSky.unused4

        print "horizon.riseRed    :", record.horizon.riseRed
        print "horizon.riseGreen  :", record.horizon.riseGreen
        print "horizon.riseBlue   :", record.horizon.riseBlue
        print "horizon.unused1    :", record.horizon.unused1
        print "horizon.dayRed     :", record.horizon.dayRed
        print "horizon.dayGreen   :", record.horizon.dayGreen
        print "horizon.dayBlue    :", record.horizon.dayBlue
        print "horizon.unused2    :", record.horizon.unused2
        print "horizon.setRed     :", record.horizon.setRed
        print "horizon.setGreen   :", record.horizon.setGreen
        print "horizon.setBlue    :", record.horizon.setBlue
        print "horizon.unused3    :", record.horizon.unused3
        print "horizon.nightRed   :", record.horizon.nightRed
        print "horizon.nightGreen :", record.horizon.nightGreen
        print "horizon.nightBlue  :", record.horizon.nightBlue
        print "horizon.unused4    :", record.horizon.unused4

        print "upperClouds.riseRed    :", record.upperClouds.riseRed
        print "upperClouds.riseGreen  :", record.upperClouds.riseGreen
        print "upperClouds.riseBlue   :", record.upperClouds.riseBlue
        print "upperClouds.unused1    :", record.upperClouds.unused1
        print "upperClouds.dayRed     :", record.upperClouds.dayRed
        print "upperClouds.dayGreen   :", record.upperClouds.dayGreen
        print "upperClouds.dayBlue    :", record.upperClouds.dayBlue
        print "upperClouds.unused2    :", record.upperClouds.unused2
        print "upperClouds.setRed     :", record.upperClouds.setRed
        print "upperClouds.setGreen   :", record.upperClouds.setGreen
        print "upperClouds.setBlue    :", record.upperClouds.setBlue
        print "upperClouds.unused3    :", record.upperClouds.unused3
        print "upperClouds.nightRed   :", record.upperClouds.nightRed
        print "upperClouds.nightGreen :", record.upperClouds.nightGreen
        print "upperClouds.nightBlue  :", record.upperClouds.nightBlue
        print "upperClouds.unused4    :", record.upperClouds.unused4
        
        print "fogDayNear   :", record.fogDayNear
        print "fogDayFar    :", record.fogDayFar
        print "fogNightNear :", record.fogNightNear
        print "fogNightFar  :", record.fogNightFar

        print "eyeAdaptSpeed  :", record.eyeAdaptSpeed
        print "blurRadius     :", record.blurRadius
        print "blurPasses     :", record.blurPasses
        print "emissiveMult   :", record.emissiveMult
        print "targetLum      :", record.targetLum
        print "upperLumClamp  :", record.upperLumClamp
        print "brightScale    :", record.brightScale
        print "brightClamp    :", record.brightClamp
        print "lumRampNoTex   :", record.lumRampNoTex
        print "lumRampMin     :", record.lumRampMin
        print "lumRampMax     :", record.lumRampMax
        print "sunlightDimmer :", record.sunlightDimmer
        print "grassDimmer    :", record.grassDimmer
        print "treeDimmer     :", record.treeDimmer
                                        
        print "windSpeed       :", record.windSpeed
        print "lowerCloudSpeed :", record.lowerCloudSpeed
        print "upperCloudSpeed :", record.upperCloudSpeed
        print "transDelta      :", record.transDelta
        print "sunGlare        :", record.sunGlare
        print "sunDamage       :", record.sunDamage
        print "rainFadeIn      :", record.rainFadeIn
        print "rainFadeOut     :", record.rainFadeOut
        print "boltFadeIn      :", record.boltFadeIn
        print "boltFadeOut     :", record.boltFadeOut
        print "boltFrequency   :", record.boltFrequency
        print "weatherType     :", record.weatherType
        print "boltRed         :", record.boltRed
        print "boltGreen       :", record.boltGreen
        print "boltBlue        :", record.boltBlue
        print "sounds"
        for sound in record.sounds:
            print "  sound: %08X, type: %u" % (sound.sound, sound.type)
        break

    print "WTHR:Create Record Test"
    newRecord = newMod.createWTHRRecord()
    print "WTHR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WTHRWarTest"
    newRecord.lowerLayer = r"WTHR\Test1\e.dds"
    newRecord.upperLayer = r"WTHR\Test2\d.dds"
    print "modPath..."
    newRecord.modPath = r"WTHR\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    newRecord.upperSky.riseRed = 1
    newRecord.upperSky.riseGreen = 2
    newRecord.upperSky.riseBlue = 3
    newRecord.upperSky.unused1 = [1]
    newRecord.upperSky.dayRed = 4
    newRecord.upperSky.dayGreen = 5
    newRecord.upperSky.dayBlue = 6
    newRecord.upperSky.unused2 = [2]
    newRecord.upperSky.setRed = 7
    newRecord.upperSky.setGreen = 8
    newRecord.upperSky.setBlue = 9
    newRecord.upperSky.unused3 = [3]
    newRecord.upperSky.nightRed = 10
    newRecord.upperSky.nightGreen = 11
    newRecord.upperSky.nightBlue = 12
    newRecord.upperSky.unused4 = [4]               
    newRecord.fog.riseRed = 13
    newRecord.fog.riseGreen = 14
    newRecord.fog.riseBlue = 15
    newRecord.fog.unused1 = [4]
    newRecord.fog.dayRed = 16
    newRecord.fog.dayGreen = 17
    newRecord.fog.dayBlue = 18
    newRecord.fog.unused2 = [4]
    newRecord.fog.setRed = 19
    newRecord.fog.setGreen = 20
    newRecord.fog.setBlue = 21
    newRecord.fog.unused3 = [4]
    newRecord.fog.nightRed = 22
    newRecord.fog.nightGreen = 23
    newRecord.fog.nightBlue = 24
    newRecord.fog.unused4 = [4]                 
    newRecord.lowerClouds.riseRed = 25
    newRecord.lowerClouds.riseGreen = 26
    newRecord.lowerClouds.riseBlue = 27
    newRecord.lowerClouds.unused1 = [4]
    newRecord.lowerClouds.dayRed = 28
    newRecord.lowerClouds.dayGreen = 29
    newRecord.lowerClouds.dayBlue = 30
    newRecord.lowerClouds.unused2 = [4]
    newRecord.lowerClouds.setRed = 31
    newRecord.lowerClouds.setGreen = 32
    newRecord.lowerClouds.setBlue = 33
    newRecord.lowerClouds.unused3 = [4]
    newRecord.lowerClouds.nightRed = 34
    newRecord.lowerClouds.nightGreen = 35
    newRecord.lowerClouds.nightBlue = 36
    newRecord.lowerClouds.unused4 = [4]                    
    newRecord.ambient.riseRed = 37
    newRecord.ambient.riseGreen = 38
    newRecord.ambient.riseBlue = 39
    newRecord.ambient.unused1 = [4]
    newRecord.ambient.dayRed = 40
    newRecord.ambient.dayGreen = 41
    newRecord.ambient.dayBlue = 42
    newRecord.ambient.unused2 = [4]
    newRecord.ambient.setRed = 43
    newRecord.ambient.setGreen = 44
    newRecord.ambient.setBlue = 45
    newRecord.ambient.unused3 = [4]
    newRecord.ambient.nightRed = 46
    newRecord.ambient.nightGreen = 47
    newRecord.ambient.nightBlue = 48
    newRecord.ambient.unused4 = [4]                    
    newRecord.sunlight.riseRed = 49
    newRecord.sunlight.riseGreen = 50
    newRecord.sunlight.riseBlue = 51
    newRecord.sunlight.unused1 = [4]
    newRecord.sunlight.dayRed = 52
    newRecord.sunlight.dayGreen = 53
    newRecord.sunlight.dayBlue = 54
    newRecord.sunlight.unused2 = [4]
    newRecord.sunlight.setRed = 55
    newRecord.sunlight.setGreen = 56
    newRecord.sunlight.setBlue = 57
    newRecord.sunlight.unused3 = [4]
    newRecord.sunlight.nightRed = 58
    newRecord.sunlight.nightGreen = 59
    newRecord.sunlight.nightBlue = 60
    newRecord.sunlight.unused4 = [4]                  
    newRecord.sun.riseRed = 61
    newRecord.sun.riseGreen = 62
    newRecord.sun.riseBlue = 63
    newRecord.sun.unused1 = [4]
    newRecord.sun.dayRed = 64
    newRecord.sun.dayGreen = 65
    newRecord.sun.dayBlue = 66
    newRecord.sun.unused2 = [4]
    newRecord.sun.setRed = 67
    newRecord.sun.setGreen = 68
    newRecord.sun.setBlue = 69
    newRecord.sun.unused3 = [4]
    newRecord.sun.nightRed = 70
    newRecord.sun.nightGreen = 71
    newRecord.sun.nightBlue = 72
    newRecord.sun.unused4 = [4]                    
    newRecord.stars.riseRed = 73
    newRecord.stars.riseGreen = 74
    newRecord.stars.riseBlue = 75
    newRecord.stars.unused1 = [4]
    newRecord.stars.dayRed = 76
    newRecord.stars.dayGreen = 77
    newRecord.stars.dayBlue = 78
    newRecord.stars.unused2 = [4]
    newRecord.stars.setRed = 79
    newRecord.stars.setGreen = 80
    newRecord.stars.setBlue = 81
    newRecord.stars.unused3 = [4]
    newRecord.stars.nightRed = 82
    newRecord.stars.nightGreen = 83
    newRecord.stars.nightBlue = 84
    newRecord.stars.unused4 = [4]                    
    newRecord.lowerSky.riseRed = 85
    newRecord.lowerSky.riseGreen = 86
    newRecord.lowerSky.riseBlue = 87
    newRecord.lowerSky.unused1 = [4]
    newRecord.lowerSky.dayRed = 88
    newRecord.lowerSky.dayGreen = 89
    newRecord.lowerSky.dayBlue = 90
    newRecord.lowerSky.unused2 = [4]
    newRecord.lowerSky.setRed = 91
    newRecord.lowerSky.setGreen = 92
    newRecord.lowerSky.setBlue = 93
    newRecord.lowerSky.unused3 = [4]
    newRecord.lowerSky.nightRed = 94
    newRecord.lowerSky.nightGreen = 95
    newRecord.lowerSky.nightBlue = 96
    newRecord.lowerSky.unused4 = [4]                    
    newRecord.horizon.riseRed = 97
    newRecord.horizon.riseGreen = 98
    newRecord.horizon.riseBlue = 99
    newRecord.horizon.unused1 = [4]
    newRecord.horizon.dayRed = 100
    newRecord.horizon.dayGreen = 101
    newRecord.horizon.dayBlue = 102
    newRecord.horizon.unused2 = [4]
    newRecord.horizon.setRed = 103
    newRecord.horizon.setGreen = 104
    newRecord.horizon.setBlue = 105
    newRecord.horizon.unused3 = [4]
    newRecord.horizon.nightRed = 106
    newRecord.horizon.nightGreen = 107
    newRecord.horizon.nightBlue = 108
    newRecord.horizon.unused4 = [4]                    
    newRecord.upperClouds.riseRed = 109
    newRecord.upperClouds.riseGreen = 110
    newRecord.upperClouds.riseBlue = 111
    newRecord.upperClouds.unused1 = [4]
    newRecord.upperClouds.dayRed = 112
    newRecord.upperClouds.dayGreen = 113
    newRecord.upperClouds.dayBlue = 114
    newRecord.upperClouds.unused2 = [4]
    newRecord.upperClouds.setRed = 115
    newRecord.upperClouds.setGreen = 116
    newRecord.upperClouds.setBlue = 117
    newRecord.upperClouds.unused3 = [4]
    newRecord.upperClouds.nightRed = 118
    newRecord.upperClouds.nightGreen = 119
    newRecord.upperClouds.nightBlue = 120
    newRecord.upperClouds.unused4 = [4]

    newRecord.fogDayNear = 1.1
    newRecord.fogDayFar = 1.2
    newRecord.fogNightNear = 1.3
    newRecord.fogNightFar = 1.4
                                        
    newRecord.eyeAdaptSpeed = 1.5
    newRecord.blurRadius = 1.6
    newRecord.blurPasses = 1.7
    newRecord.emissiveMult = 1.8
    newRecord.targetLum = 1.9
    newRecord.upperLumClamp = 2.0
    newRecord.brightScale = 2.1
    newRecord.brightClamp = 2.2
    newRecord.lumRampNoTex = 2.3
    newRecord.lumRampMin = 2.4
    newRecord.lumRampMax = 2.5
    newRecord.sunlightDimmer = 2.6
    newRecord.grassDimmer = 2.7
    newRecord.treeDimmer = 2.8
                                        
    newRecord.windSpeed = 1
    newRecord.lowerCloudSpeed = 2
    newRecord.upperCloudSpeed = 3
    newRecord.transDelta = 4
    newRecord.sunGlare = 5
    newRecord.sunDamage = 6
    newRecord.rainFadeIn = 7
    newRecord.rainFadeOut = 8
    newRecord.boltFadeIn = 9
    newRecord.boltFadeOut = 10
    newRecord.boltFrequency = 11
    newRecord.weatherType = 12
    newRecord.boltRed = 13
    newRecord.boltGreen = 14
    newRecord.boltBlue = 15

    newSound = newRecord.newSoundsElement()
    newSound.sound = 7
    newSound.type = 0

    newSound = newRecord.newSoundsElement()
    newSound.sound = 8
    newSound.type = 1
    
    newSound = newRecord.newSoundsElement()
    newSound.sound = 9
    newSound.type = 2
    
    newSound = newRecord.newSoundsElement()
    newSound.sound = 10
    newSound.type = 3
    
    newRecord.sounds = [newRecord.sounds[0], newRecord.sounds[3], newRecord.sounds[2]]
    
    print "WTHR:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "lowerLayer :", newRecord.lowerLayer
    print "upperLayer :", newRecord.upperLayer
    
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "upperSky.riseRed    :", newRecord.upperSky.riseRed
    print "upperSky.riseGreen  :", newRecord.upperSky.riseGreen
    print "upperSky.riseBlue   :", newRecord.upperSky.riseBlue
    print "upperSky.unused1    :", newRecord.upperSky.unused1
    print "upperSky.dayRed     :", newRecord.upperSky.dayRed
    print "upperSky.dayGreen   :", newRecord.upperSky.dayGreen
    print "upperSky.dayBlue    :", newRecord.upperSky.dayBlue
    print "upperSky.unused2    :", newRecord.upperSky.unused2
    print "upperSky.setRed     :", newRecord.upperSky.setRed
    print "upperSky.setGreen   :", newRecord.upperSky.setGreen
    print "upperSky.setBlue    :", newRecord.upperSky.setBlue
    print "upperSky.unused3    :", newRecord.upperSky.unused3
    print "upperSky.nightRed   :", newRecord.upperSky.nightRed
    print "upperSky.nightGreen :", newRecord.upperSky.nightGreen
    print "upperSky.nightBlue  :", newRecord.upperSky.nightBlue
    print "upperSky.unused4    :", newRecord.upperSky.unused4
    
    print "fog.riseRed    :", newRecord.fog.riseRed
    print "fog.riseGreen  :", newRecord.fog.riseGreen
    print "fog.riseBlue   :", newRecord.fog.riseBlue
    print "fog.unused1    :", newRecord.fog.unused1
    print "fog.dayRed     :", newRecord.fog.dayRed
    print "fog.dayGreen   :", newRecord.fog.dayGreen
    print "fog.dayBlue    :", newRecord.fog.dayBlue
    print "fog.unused2    :", newRecord.fog.unused2
    print "fog.setRed     :", newRecord.fog.setRed
    print "fog.setGreen   :", newRecord.fog.setGreen
    print "fog.setBlue    :", newRecord.fog.setBlue
    print "fog.unused3    :", newRecord.fog.unused3
    print "fog.nightRed   :", newRecord.fog.nightRed
    print "fog.nightGreen :", newRecord.fog.nightGreen
    print "fog.nightBlue  :", newRecord.fog.nightBlue
    print "fog.unused4    :", newRecord.fog.unused4

    print "lowerClouds.riseRed    :", newRecord.lowerClouds.riseRed
    print "lowerClouds.riseGreen  :", newRecord.lowerClouds.riseGreen
    print "lowerClouds.riseBlue   :", newRecord.lowerClouds.riseBlue
    print "lowerClouds.unused1    :", newRecord.lowerClouds.unused1
    print "lowerClouds.dayRed     :", newRecord.lowerClouds.dayRed
    print "lowerClouds.dayGreen   :", newRecord.lowerClouds.dayGreen
    print "lowerClouds.dayBlue    :", newRecord.lowerClouds.dayBlue
    print "lowerClouds.unused2    :", newRecord.lowerClouds.unused2
    print "lowerClouds.setRed     :", newRecord.lowerClouds.setRed
    print "lowerClouds.setGreen   :", newRecord.lowerClouds.setGreen
    print "lowerClouds.setBlue    :", newRecord.lowerClouds.setBlue
    print "lowerClouds.unused3    :", newRecord.lowerClouds.unused3
    print "lowerClouds.nightRed   :", newRecord.lowerClouds.nightRed
    print "lowerClouds.nightGreen :", newRecord.lowerClouds.nightGreen
    print "lowerClouds.nightBlue  :", newRecord.lowerClouds.nightBlue
    print "lowerClouds.unused4    :", newRecord.lowerClouds.unused4
    
    print "ambient.riseRed    :", newRecord.ambient.riseRed
    print "ambient.riseGreen  :", newRecord.ambient.riseGreen
    print "ambient.riseBlue   :", newRecord.ambient.riseBlue
    print "ambient.unused1    :", newRecord.ambient.unused1
    print "ambient.dayRed     :", newRecord.ambient.dayRed
    print "ambient.dayGreen   :", newRecord.ambient.dayGreen
    print "ambient.dayBlue    :", newRecord.ambient.dayBlue
    print "ambient.unused2    :", newRecord.ambient.unused2
    print "ambient.setRed     :", newRecord.ambient.setRed
    print "ambient.setGreen   :", newRecord.ambient.setGreen
    print "ambient.setBlue    :", newRecord.ambient.setBlue
    print "ambient.unused3    :", newRecord.ambient.unused3
    print "ambient.nightRed   :", newRecord.ambient.nightRed
    print "ambient.nightGreen :", newRecord.ambient.nightGreen
    print "ambient.nightBlue  :", newRecord.ambient.nightBlue
    print "ambient.unused4    :", newRecord.ambient.unused4

    print "sunlight.riseRed    :", newRecord.sunlight.riseRed
    print "sunlight.riseGreen  :", newRecord.sunlight.riseGreen
    print "sunlight.riseBlue   :", newRecord.sunlight.riseBlue
    print "sunlight.unused1    :", newRecord.sunlight.unused1
    print "sunlight.dayRed     :", newRecord.sunlight.dayRed
    print "sunlight.dayGreen   :", newRecord.sunlight.dayGreen
    print "sunlight.dayBlue    :", newRecord.sunlight.dayBlue
    print "sunlight.unused2    :", newRecord.sunlight.unused2
    print "sunlight.setRed     :", newRecord.sunlight.setRed
    print "sunlight.setGreen   :", newRecord.sunlight.setGreen
    print "sunlight.setBlue    :", newRecord.sunlight.setBlue
    print "sunlight.unused3    :", newRecord.sunlight.unused3
    print "sunlight.nightRed   :", newRecord.sunlight.nightRed
    print "sunlight.nightGreen :", newRecord.sunlight.nightGreen
    print "sunlight.nightBlue  :", newRecord.sunlight.nightBlue
    print "sunlight.unused4    :", newRecord.sunlight.unused4

    print "sun.riseRed    :", newRecord.sun.riseRed
    print "sun.riseGreen  :", newRecord.sun.riseGreen
    print "sun.riseBlue   :", newRecord.sun.riseBlue
    print "sun.unused1    :", newRecord.sun.unused1
    print "sun.dayRed     :", newRecord.sun.dayRed
    print "sun.dayGreen   :", newRecord.sun.dayGreen
    print "sun.dayBlue    :", newRecord.sun.dayBlue
    print "sun.unused2    :", newRecord.sun.unused2
    print "sun.setRed     :", newRecord.sun.setRed
    print "sun.setGreen   :", newRecord.sun.setGreen
    print "sun.setBlue    :", newRecord.sun.setBlue
    print "sun.unused3    :", newRecord.sun.unused3
    print "sun.nightRed   :", newRecord.sun.nightRed
    print "sun.nightGreen :", newRecord.sun.nightGreen
    print "sun.nightBlue  :", newRecord.sun.nightBlue
    print "sun.unused4    :", newRecord.sun.unused4

    print "stars.riseRed    :", newRecord.stars.riseRed
    print "stars.riseGreen  :", newRecord.stars.riseGreen
    print "stars.riseBlue   :", newRecord.stars.riseBlue
    print "stars.unused1    :", newRecord.stars.unused1
    print "stars.dayRed     :", newRecord.stars.dayRed
    print "stars.dayGreen   :", newRecord.stars.dayGreen
    print "stars.dayBlue    :", newRecord.stars.dayBlue
    print "stars.unused2    :", newRecord.stars.unused2
    print "stars.setRed     :", newRecord.stars.setRed
    print "stars.setGreen   :", newRecord.stars.setGreen
    print "stars.setBlue    :", newRecord.stars.setBlue
    print "stars.unused3    :", newRecord.stars.unused3
    print "stars.nightRed   :", newRecord.stars.nightRed
    print "stars.nightGreen :", newRecord.stars.nightGreen
    print "stars.nightBlue  :", newRecord.stars.nightBlue
    print "stars.unused4    :", newRecord.stars.unused4

    print "lowerSky.riseRed    :", newRecord.lowerSky.riseRed
    print "lowerSky.riseGreen  :", newRecord.lowerSky.riseGreen
    print "lowerSky.riseBlue   :", newRecord.lowerSky.riseBlue
    print "lowerSky.unused1    :", newRecord.lowerSky.unused1
    print "lowerSky.dayRed     :", newRecord.lowerSky.dayRed
    print "lowerSky.dayGreen   :", newRecord.lowerSky.dayGreen
    print "lowerSky.dayBlue    :", newRecord.lowerSky.dayBlue
    print "lowerSky.unused2    :", newRecord.lowerSky.unused2
    print "lowerSky.setRed     :", newRecord.lowerSky.setRed
    print "lowerSky.setGreen   :", newRecord.lowerSky.setGreen
    print "lowerSky.setBlue    :", newRecord.lowerSky.setBlue
    print "lowerSky.unused3    :", newRecord.lowerSky.unused3
    print "lowerSky.nightRed   :", newRecord.lowerSky.nightRed
    print "lowerSky.nightGreen :", newRecord.lowerSky.nightGreen
    print "lowerSky.nightBlue  :", newRecord.lowerSky.nightBlue
    print "lowerSky.unused4    :", newRecord.lowerSky.unused4

    print "horizon.riseRed    :", newRecord.horizon.riseRed
    print "horizon.riseGreen  :", newRecord.horizon.riseGreen
    print "horizon.riseBlue   :", newRecord.horizon.riseBlue
    print "horizon.unused1    :", newRecord.horizon.unused1
    print "horizon.dayRed     :", newRecord.horizon.dayRed
    print "horizon.dayGreen   :", newRecord.horizon.dayGreen
    print "horizon.dayBlue    :", newRecord.horizon.dayBlue
    print "horizon.unused2    :", newRecord.horizon.unused2
    print "horizon.setRed     :", newRecord.horizon.setRed
    print "horizon.setGreen   :", newRecord.horizon.setGreen
    print "horizon.setBlue    :", newRecord.horizon.setBlue
    print "horizon.unused3    :", newRecord.horizon.unused3
    print "horizon.nightRed   :", newRecord.horizon.nightRed
    print "horizon.nightGreen :", newRecord.horizon.nightGreen
    print "horizon.nightBlue  :", newRecord.horizon.nightBlue
    print "horizon.unused4    :", newRecord.horizon.unused4

    print "upperClouds.riseRed    :", newRecord.upperClouds.riseRed
    print "upperClouds.riseGreen  :", newRecord.upperClouds.riseGreen
    print "upperClouds.riseBlue   :", newRecord.upperClouds.riseBlue
    print "upperClouds.unused1    :", newRecord.upperClouds.unused1
    print "upperClouds.dayRed     :", newRecord.upperClouds.dayRed
    print "upperClouds.dayGreen   :", newRecord.upperClouds.dayGreen
    print "upperClouds.dayBlue    :", newRecord.upperClouds.dayBlue
    print "upperClouds.unused2    :", newRecord.upperClouds.unused2
    print "upperClouds.setRed     :", newRecord.upperClouds.setRed
    print "upperClouds.setGreen   :", newRecord.upperClouds.setGreen
    print "upperClouds.setBlue    :", newRecord.upperClouds.setBlue
    print "upperClouds.unused3    :", newRecord.upperClouds.unused3
    print "upperClouds.nightRed   :", newRecord.upperClouds.nightRed
    print "upperClouds.nightGreen :", newRecord.upperClouds.nightGreen
    print "upperClouds.nightBlue  :", newRecord.upperClouds.nightBlue
    print "upperClouds.unused4    :", newRecord.upperClouds.unused4
    
    print "fogDayNear   :", newRecord.fogDayNear
    print "fogDayFar    :", newRecord.fogDayFar
    print "fogNightNear :", newRecord.fogNightNear
    print "fogNightFar  :", newRecord.fogNightFar

    print "eyeAdaptSpeed  :", newRecord.eyeAdaptSpeed
    print "blurRadius     :", newRecord.blurRadius
    print "blurPasses     :", newRecord.blurPasses
    print "emissiveMult   :", newRecord.emissiveMult
    print "targetLum      :", newRecord.targetLum
    print "upperLumClamp  :", newRecord.upperLumClamp
    print "brightScale    :", newRecord.brightScale
    print "brightClamp    :", newRecord.brightClamp
    print "lumRampNoTex   :", newRecord.lumRampNoTex
    print "lumRampMin     :", newRecord.lumRampMin
    print "lumRampMax     :", newRecord.lumRampMax
    print "sunlightDimmer :", newRecord.sunlightDimmer
    print "grassDimmer    :", newRecord.grassDimmer
    print "treeDimmer     :", newRecord.treeDimmer
                                    
    print "windSpeed       :", newRecord.windSpeed
    print "lowerCloudSpeed :", newRecord.lowerCloudSpeed
    print "upperCloudSpeed :", newRecord.upperCloudSpeed
    print "transDelta      :", newRecord.transDelta
    print "sunGlare        :", newRecord.sunGlare
    print "sunDamage       :", newRecord.sunDamage
    print "rainFadeIn      :", newRecord.rainFadeIn
    print "rainFadeOut     :", newRecord.rainFadeOut
    print "boltFadeIn      :", newRecord.boltFadeIn
    print "boltFadeOut     :", newRecord.boltFadeOut
    print "boltFrequency   :", newRecord.boltFrequency
    print "weatherType     :", newRecord.weatherType
    print "boltRed         :", newRecord.boltRed
    print "boltGreen       :", newRecord.boltGreen
    print "boltBlue        :", newRecord.boltBlue
    print "sounds"
    for sound in newRecord.sounds:
        print "  sound: %08X, type: %u" % (sound.sound, sound.type)
        
    print "WTHR:CopyAsOverride Test"
    for record in Current[0].WTHR:
        record.CopyAsOverride(newMod)

    print "WTHR:CopyAsNew Test"
    for record in Current[0].WTHR:
        record.CopyAsNew(newMod)

    print "WTHR:Save Test - TestWTHR.esp"
    newMod.safeSave()
    print "WTHR:Finished testing"


def TestCLMT():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCLMT.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.CLMT:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "weathers"
        for weather in record.weathers:
            print "  weather: %08X, chance: %u" % (weather.weather, weather.chance)
        print "sunPath     :", record.sunPath
        print "glarePath   :", record.glarePath
        print "modPath     :", record.modPath
        print "modb        :", record.modb
        print "modt_p      :", record.modt_p
        print "riseBegin   :", record.riseBegin
        print "riseEnd     :", record.riseEnd
        print "setBegin    :", record.setBegin
        print "setEnd      :", record.setEnd
        print "volatility  :", record.volatility
        print "phaseLength :", record.phaseLength

        break

    print "CLMT:Create Record Test"
    newRecord = newMod.createCLMTRecord()
    print "CLMT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CLMTWarTest"

    newWeather = newRecord.newWeathersElement()
    newWeather.weather = 7
    newWeather.chance = 31
    
    newWeather = newRecord.newWeathersElement()
    newWeather.weather = 8
    newWeather.chance = 32

    newWeather = newRecord.newWeathersElement()
    newWeather.weather = 9
    newWeather.chance = 33
    
    newWeather = newRecord.newWeathersElement()
    newWeather.weather = 10
    newWeather.chance = 34
    
    newRecord.weathers = [newRecord.weathers[3], newRecord.weathers[2], newRecord.weathers[0]]
    newRecord.sunPath = r"CLMT\sunPath\1.nif"
    newRecord.glarePath = r"CLMT\glarePath\1.nif"
    print "modPath..."
    newRecord.modPath = r"CLMT\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.36
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    newRecord.riseBegin = 1
    newRecord.riseEnd = 2
    newRecord.setBegin = 3
    newRecord.setEnd = 4
    newRecord.volatility = 5
    newRecord.phaseLength = 6

    print "CLMT:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "weathers"
    for weather in newRecord.weathers:
        print "  weather: %08X, chance: %u" % (weather.weather, weather.chance)
    print "sunPath     :", newRecord.sunPath
    print "glarePath   :", newRecord.glarePath
    print "modPath     :", newRecord.modPath
    print "modb        :", newRecord.modb
    print "modt_p      :", newRecord.modt_p
    print "riseBegin   :", newRecord.riseBegin
    print "riseEnd     :", newRecord.riseEnd
    print "setBegin    :", newRecord.setBegin
    print "setEnd      :", newRecord.setEnd
    print "volatility  :", newRecord.volatility
    print "phaseLength :", newRecord.phaseLength    
    print "CLMT:CopyAsOverride Test"
    for record in Current[0].CLMT:
        record.CopyAsOverride(newMod)

    print "CLMT:CopyAsNew Test"
    for record in Current[0].CLMT:
        record.CopyAsNew(newMod)

    print "CLMT:Save Test - TestCLMT.esp"
    newMod.safeSave()
    print "CLMT:Finished testing"


def TestREGN():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestREGN.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.REGN:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "iconPath   :", record.iconPath
        print "mapRed     :", record.mapRed
        print "mapGreen   :", record.mapGreen
        print "mapBlue    :", record.mapBlue
        print "unused1    :", record.unused1
        print "worldspace : %08X" % record.worldspace
        print "areas"
        for area in record.areas:
            print "  edgeFalloff :", area.edgeFalloff
            print "  points"
            for point in area.points:
                print "    posX:%.6f, posY:%.6f" % (point.posX, point.posY)
            print
        print "entries"
        for entry in record.entries:
            print "  entryType :", entry.entryType
            print "  flags     :", entry.flags
            print "  priority  :", entry.priority
            print "  unused1   :", entry.unused1
            print "  objects"
            for recObject in entry.objects:
                print "    objectId        : %08X" % recObject.objectId
                print "    parentIndex     :", recObject.parentIndex
                print "    unused1         :", recObject.unused1
                print "    density         :", recObject.density
                print "    clustering      :", recObject.clustering
                print "    minSlope        :", recObject.minSlope
                print "    maxSlope        :", recObject.maxSlope
                print "    flags           :", recObject.flags
                print "    radiusWRTParent :", recObject.radiusWRTParent
                print "    radius          :", recObject.radius
                print "    unk1            :", recObject.unk1
                print "    maxHeight       :", recObject.maxHeight
                print "    sink            :", recObject.sink
                print "    sinkVar         :", recObject.sinkVar
                print "    angleVarX       :", recObject.angleVarX
                print "    angleVarY       :", recObject.angleVarY
                print "    angleVarZ       :", recObject.angleVarZ
                print "    unused2         :", recObject.unused2
                print "    unk2            :", recObject.unk2
                print
            print "  mapName   :", entry.mapName
            print "  iconPath  :", entry.iconPath
            print "  grasses"
            for grass in entry.grasses:
                print "    grass : %08X" % grass.grass,
                print ", unk1 :", grass.unk1
                print
            print "  musicType :", entry.musicType
            print "  sounds"
            for sound in entry.sounds:
                print "    sound  : %08X" % sound.sound
                print "    flags  :", sound.flags
                print "    chance :", sound.chance
                print
            print "  weathers"
            for weather in entry.weathers:
                print "    weather : %08X" % weather.weather
                print "    chance  :", weather.chance
                print
            print
        break

    print "REGN:Create Record Test"
    newRecord = newMod.createREGNRecord()
    print "REGN:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "REGNWarTest"

    print "iconPath..."
    newRecord.iconPath = r"REGN\path\test.dds"
    newRecord.mapRed = 1
    newRecord.mapGreen = 2
    newRecord.mapBlue = 3
    newRecord.unused1 = [4]
    newRecord.worldspace = 7

    newArea = newRecord.newAreasElement()
    newArea.edgeFalloff = 1024
    newPoint = newArea.newPointsElement()
    newPoint.posX = 1
    newPoint.posY = 2
    newPoint = newArea.newPointsElement()
    newPoint.posX = 3.0
    newPoint.posY = 4.0
    newPoint = newArea.newPointsElement()
    newPoint.posX = 5.0
    newPoint.posY = 6.0
    newPoint = newArea.newPointsElement()
    newPoint.posX = 7.0
    newPoint.posY = 8.0
    newPoint = newArea.newPointsElement()
    newPoint.posX = 9.0
    newPoint.posY = 10.0
    newPoint = newArea.newPointsElement()
    newPoint.posX = 11.0
    newPoint.posY = 12.0
    newPoint = newArea.newPointsElement()
    newPoint.posX = 13.0
    newPoint.posY = 14.0
    newPoint = newArea.newPointsElement()
    newPoint.posX = 15.0
    newPoint.posY = 16.0
    newPoint = newArea.newPointsElement()
    newPoint.posX = 17.0
    newPoint.posY = 18.0

    newArea.points = [newArea.points[0], newArea.points[2], newArea.points[4], newArea.points[6], newArea.points[8]]
    
    newArea = newRecord.newAreasElement()
    newArea.edgeFalloff = 1025
    newPoint = newArea.newPointsElement()
    newPoint.posX = 1.1
    newPoint.posY = 2.1
    newPoint = newArea.newPointsElement()
    newPoint.posX = 3.1
    newPoint.posY = 4.1
    newPoint = newArea.newPointsElement()
    newPoint.posX = 5.1
    newPoint.posY = 6.1
    newPoint = newArea.newPointsElement()
    newPoint.posX = 7.1
    newPoint.posY = 8.1
    newPoint = newArea.newPointsElement()
    newPoint.posX = 9.1
    newPoint.posY = 10.1
    newPoint = newArea.newPointsElement()
    newPoint.posX = 11.1
    newPoint.posY = 12.1
    newPoint = newArea.newPointsElement()
    newPoint.posX = 13.1
    newPoint.posY = 14.1
    newPoint = newArea.newPointsElement()
    newPoint.posX = 15.1
    newPoint.posY = 16.1
    newPoint = newArea.newPointsElement()
    newPoint.posX = 17.1
    newPoint.posY = 18.1

    newArea = newRecord.newAreasElement()
    newArea.edgeFalloff = 1026
    newPoint = newArea.newPointsElement()
    newPoint.posX = 1.2
    newPoint.posY = 2.2
    newPoint = newArea.newPointsElement()
    newPoint.posX = 3.2
    newPoint.posY = 4.2
    newPoint = newArea.newPointsElement()
    newPoint.posX = 5.2
    newPoint.posY = 6.2
    newPoint = newArea.newPointsElement()
    newPoint.posX = 7.2
    newPoint.posY = 8.2
    newPoint = newArea.newPointsElement()
    newPoint.posX = 9.2
    newPoint.posY = 10.2
    newPoint = newArea.newPointsElement()
    newPoint.posX = 11.2
    newPoint.posY = 12.2
    newPoint = newArea.newPointsElement()
    newPoint.posX = 13.2
    newPoint.posY = 14.2
    newPoint = newArea.newPointsElement()
    newPoint.posX = 15.2
    newPoint.posY = 16.2
    newPoint = newArea.newPointsElement()
    newPoint.posX = 17.2
    newPoint.posY = 18.2

    newRecord.areas = [newRecord.areas[2], newRecord.areas[0]]    

    newEntry = newRecord.newEntriesElement()
    newEntry.entryType = 2 ##Objects
##    newEntry.entryType = 3 ##Weathers
##    newEntry.entryType = 4 ##map
##    newEntry.entryType = 5 ##icon
##    newEntry.entryType = 6 ##Grasses
##    newEntry.entryType = 7 ##Sounds
    newEntry.flags = 2
    newEntry.priority = 3
    newEntry.unused1 = [1,2]

    newObject = newEntry.newObjectsElement()
    newObject.objectId = 7
    newObject.unused1 = [1,2]
    newObject.density = 1
    newObject.clustering = 2
    newObject.minSlope = 3
    newObject.maxSlope = 4
    newObject.flags = 5
    newObject.radiusWRTParent = 6
    newObject.radius = 7
    newObject.unk1 = [5,6,7,8]
    newObject.maxHeight = 8
    newObject.sink = 9
    newObject.sinkVar = 10
    newObject.angleVarX = 12
    newObject.angleVarY = 13
    newObject.angleVarZ = 14
    newObject.unused2 = [3,4]
    newObject.unk2 = [1,2,3,4]
    
    newObject = newEntry.newObjectsElement()
    newObject.objectId = 8
    newObject.unused1 = [1,2]
    newObject.density = 2
    newObject.clustering = 3
    newObject.minSlope = 4
    newObject.maxSlope = 5
    newObject.flags = 6
    newObject.radiusWRTParent = 7
    newObject.radius = 8
    newObject.unk1 = [5,6,7,8]
    newObject.maxHeight = 9
    newObject.sink = 10
    newObject.sinkVar = 11
    newObject.angleVarX = 13
    newObject.angleVarY = 14
    newObject.angleVarZ = 15
    newObject.unused2 = [3,4]
    newObject.unk2 = [1,2,3,4]

    newObject = newEntry.newObjectsElement()
    newObject.objectId = 9
    newObject.unused1 = [1,2]
    newObject.density = 3
    newObject.clustering = 4
    newObject.minSlope = 5
    newObject.maxSlope = 6
    newObject.flags = 7
    newObject.radiusWRTParent = 8
    newObject.radius = 9
    newObject.unk1 = [5,6,7,8]
    newObject.maxHeight = 10
    newObject.sink = 11
    newObject.sinkVar = 12
    newObject.angleVarX = 14
    newObject.angleVarY = 15
    newObject.angleVarZ = 16
    newObject.unused2 = [3,4]
    newObject.unk2 = [1,2,3,4]

    newEntry.objects = [newEntry.objects[2], newEntry.objects[0]]    

##    newWeather = newEntry.newWeathersElement()
##    newWeather.weather = 7
##    newWeather.chance = 10
##    newWeather = newEntry.newWeathersElement()
##    newWeather.weather = 8
##    newWeather.chance = 11
##    newWeather = newEntry.newWeathersElement()
##    newWeather.weather = 9
##    newWeather.chance = 12
##    newWeather = newEntry.newWeathersElement()
##    newWeather.weather = 10
##    newWeather.chance = 13
##    newWeather = newEntry.newWeathersElement()
##    newWeather.weather = 11
##    newWeather.chance = 14
##    newEntry.weathers = [newEntry.weathers[3], newEntry.weathers[0], newEntry.weathers[4]]
    
##    newEntry.mapName = r"Durgh"
##    newEntry.iconPath = r"OBSOLETE\Test\ICON.dds"

##    newGrass = newEntry.newGrassesElement()
##    newGrass.grass = 7
##    newGrass.unk1 = [1,2,3,4]
##    newGrass = newEntry.newGrassesElement()
##    newGrass.grass = 8
##    newGrass.unk1 = [2,2,3,4]
##    newGrass = newEntry.newGrassesElement()
##    newGrass.grass = 9
##    newGrass.unk1 = [3,2,3,4]
##    newGrass = newEntry.newGrassesElement()
##    newGrass.grass = 10
##    newGrass.unk1 = [4,2,3,4]
##    newEntry.grasses = [newEntry.grasses[2], newEntry.grasses[0]]  

##    newSound = newEntry.newSoundsElement()
##    newSound.sound = 7
##    newSound.flags = 1
##    newSound.chance = 10
##    newSound = newEntry.newSoundsElement()
##    newSound.sound = 8
##    newSound.flags = 2
##    newSound.chance = 11
##    newSound = newEntry.newSoundsElement()
##    newSound.sound = 9
##    newSound.flags = 3
##    newSound.chance = 12
##    newSound = newEntry.newSoundsElement()
##    newSound.sound = 10
##    newSound.flags = 4
##    newSound.chance = 13
##    newEntry.sounds = [newEntry.sounds[2], newEntry.sounds[0]]
    
    print "REGN:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "iconPath   :", newRecord.iconPath
    print "mapRed     :", newRecord.mapRed
    print "mapGreen   :", newRecord.mapGreen
    print "mapBlue    :", newRecord.mapBlue
    print "unused1    :", newRecord.unused1
    print "worldspace : %08X" % newRecord.worldspace
    print "areas"
    for area in newRecord.areas:
        print "  edgeFalloff :", area.edgeFalloff
        print "  points"
        for point in area.points:
            print "    posX:%.6f, posY:%.6f" % (point.posX, point.posY)
        print
    print "entries"
    for entry in newRecord.entries:
        print "  entryType :", entry.entryType
        print "  flags     :", entry.flags
        print "  priority  :", entry.priority
        print "  unused1   :", entry.unused1
        print "  objects"
        for recObject in entry.objects:
            print "    objectId        : %08X" % recObject.objectId
            print "    parentIndex     :", recObject.parentIndex
            print "    unused1         :", recObject.unused1
            print "    density         :", recObject.density
            print "    clustering      :", recObject.clustering
            print "    minSlope        :", recObject.minSlope
            print "    maxSlope        :", recObject.maxSlope
            print "    flags           :", recObject.flags
            print "    radiusWRTParent :", recObject.radiusWRTParent
            print "    radius          :", recObject.radius
            print "    unk1            :", recObject.unk1
            print "    maxHeight       :", recObject.maxHeight
            print "    sink            :", recObject.sink
            print "    sinkVar         :", recObject.sinkVar
            print "    angleVarX       :", recObject.angleVarX
            print "    angleVarY       :", recObject.angleVarY
            print "    angleVarZ       :", recObject.angleVarZ
            print "    unused2         :", recObject.unused2
            print "    unk2            :", recObject.unk2
            print
        print "  mapName   :", entry.mapName
        print "  iconPath  :", entry.iconPath
        print "  grasses"
        for grass in entry.grasses:
            print "    grass : %08X" % grass.grass,
            print ", unk1 :", grass.unk1
        print "  musicType :", entry.musicType
        print "  sounds"
        for sound in entry.sounds:
            print "    sound  : %08X" % sound.sound
            print "    flags  :", sound.flags
            print "    chance :", sound.chance
        print "  weathers"
        for weather in entry.weathers:
            print "    weather : %08X" % weather.weather
            print "    chance  :", weather.chance
        print
    print "REGN:CopyAsOverride Test"
    for record in Current[0].REGN:
        record.CopyAsOverride(newMod)

    print "REGN:CopyAsNew Test"
    for record in Current[0].REGN:
        record.CopyAsNew(newMod)

    print "REGN:Save Test - TestREGN.esp"
    newMod.safeSave()
    print "REGN:Finished testing"



def TestCELL():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCELL.esp", True)
    Current.minimalLoad(LoadMasters=True)
    x = 0
    for record in Current.CELL:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "full             :", record.full
        print "flags            :", record.flags
        print "ambientRed       :", record.ambientRed
        print "ambientGreen     :", record.ambientGreen
        print "ambientBlue      :", record.ambientBlue
        print "unused1          :", record.unused1
        print "directionalRed   :", record.directionalRed
        print "directionalGreen :", record.directionalGreen
        print "directionalBlue  :", record.directionalBlue
        print "unused2          :", record.unused2
        print "fogRed           :", record.fogRed
        print "fogGreen         :", record.fogGreen
        print "fogBlue          :", record.fogBlue
        print "unused3          :", record.unused3
        print "fogNear          :", record.fogNear
        print "fogFar           :", record.fogFar
        print "directionalXY    :", record.directionalXY
        print "directionalZ     :", record.directionalZ
        print "directionalFade  :", record.directionalFade
        print "fogClip          :", record.fogClip
        print "music            :", record.music
        formID = record.owner
        if(formID != None):
            print "owner            : %08X" % formID
        else:
            print "owner            :", formID
            
        print "rank             :", record.rank
        formID = record.globalVariable
        if(formID != None):
            print "globalVariable   : %08X" % formID
        else:
            print "globalVariable   :", formID        
        print "climate          : %08X" % record.climate
        print "waterHeight      :", record.waterHeight
        print "regions          :", record.regions
        print "posX             :", record.posX
        print "posY             :", record.posY
        print "water            : %08X" % record.water

        print "Placed NPCs"
        for achr in record.ACHR:
            print
            print "  fid    : %08X" % achr.fid
            print "  flags1 :", achr.flags1
            print "  flags2 :", achr.flags2
            print "  eid    :", achr.eid
            
            print "  base              : %08X" % achr.base
            formID = achr.unknownXPCIFormID
            if(formID != None):
                print "  unknownXPCIFormID : %08X" % formID
            else:
                print "  unknownXPCIFormID :", formID
            print "  unknownXPCIString :", achr.unknownXPCIString
            print "  lod1              :", achr.lod1
            print "  lod2              :", achr.lod2
            print "  lod3              :", achr.lod3
            formID = achr.parent
            if(formID != None):
                print "  parent            : %08X" % formID
            else:
                print "  parent            :", formID
            print "  parentFlags       :", achr.parentFlags
            print "  unused1           :", achr.unused1
            formID = achr.merchantContainer
            if(formID != None):
                print "  merchantContainer : %08X" % formID
            else:
                print "  merchantContainer :", formID
            formID = achr.horse
            if(formID != None):
                print "  horse             : %08X" % formID
            else:
                print "  horse             :", formID
            print "  xrgd_p            :", achr.xrgd_p
            print "  scale             :", achr.scale
            print "  posX              :", achr.posX
            print "  posY              :", achr.posY
            print "  posZ              :", achr.posZ
            print "  rotX              :", achr.rotX
            print "  rotY              :", achr.rotY
            print "  rotZ              :", achr.rotZ
            break

        print "Placed Creatures"
        for acre in record.ACRE:
            print
            print "  fid    : %08X" % acre.fid
            print "  flags1 :", acre.flags1
            print "  flags2 :", acre.flags2
            print "  eid    :", acre.eid

            print "  base           : %08X" % acre.base
            formID = acre.owner
            if(formID != None):
                print "  owner          : %08X" % formID
            else:
                print "  owner          :", formID
                
            print "  rank           :", acre.rank
            formID = acre.globalVariable
            if(formID != None):
                print "  globalVariable : %08X" % formID
            else:
                print "  globalVariable :", formID
            formID = acre.parent
            if(formID != None):
                print "  parent         : %08X" % formID
            else:
                print "  parent         :", formID
            print "  parentFlags    :", acre.parentFlags
            print "  unused1        :", acre.unused1
            print "  xrgd_p         :", acre.xrgd_p
            print "  scale          :", acre.scale
            print "  posX           :", acre.posX
            print "  posY           :", acre.posY
            print "  posZ           :", acre.posZ
            print "  rotX           :", acre.rotX
            print "  rotY           :", acre.rotY
            print "  rotZ           :", acre.rotZ
            break

        print "Placed Objects"
        for refr in record.REFR:
            print
            print "  fid    : %08X" % refr.fid
            print "  flags1 :", refr.flags1
            print "  flags2 :", refr.flags2
            print "  eid    :", refr.eid
            formID = refr.base
            if(formID != None):
                print "  base              : %08X" % formID
            else:
                print "  base              :", formID
            formID = refr.destinationFormID
            if(formID != None):
                print "  destinationFormID : %08X" % formID
            else:
                print "  destinationFormID :", formID

            print "  destinationPosX   :", refr.destinationPosX
            print "  destinationPosY   :", refr.destinationPosY
            print "  destinationPosZ   :", refr.destinationPosZ
            print "  destinationRotX   :", refr.destinationRotX
            print "  destinationRotY   :", refr.destinationRotY
            print "  destinationRotZ   :", refr.destinationRotZ
            print "  lockLevel         :", refr.lockLevel
            print "  unused1           :", refr.unused1

            formID = refr.lockKey
            if(formID != None):
                print "  lockKey           : %08X" % formID
            else:
                print "  lockKey           :", formID

            print "  unused2           :", refr.unused2
            print "  lockFlags         :", refr.lockFlags
            print "  unused3           :", refr.unused3
            formID = refr.owner
            if(formID != None):
                print "  owner             : %08X" % formID
            else:
                print "  owner             :", formID
                
            print "  rank              :", refr.rank
            formID = refr.globalVariable
            if(formID != None):
                print "  globalVariable    : %08X" % formID
            else:
                print "  globalVariable    :", formID
            formID = refr.parent
            if(formID != None):
                print "  parent            : %08X" % formID
            else:
                print "  parent            :", formID
            print "  parentFlags       :", refr.parentFlags
            print "  unused4           :", refr.unused4
            formID = refr.targetFormID
            if(formID != None):
                print "  targetFormID      : %08X" % formID
            else:
                print "  targetFormID      :", formID
            print "  seed              :", refr.seed
            print "  seedOffset        :", refr.seedOffset
            print "  lod1              :", refr.lod1
            print "  lod2              :", refr.lod2
            print "  lod3              :", refr.lod3
            print "  charge            :", refr.charge
            print "  health            :", refr.health
            formID = refr.unknownXPCIFormID
            if(formID != None):
                print "  unknownXPCIFormID : %08X" % formID
            else:
                print "  unknownXPCIFormID :", formID
            print "  unknownXPCIString :", refr.unknownXPCIString
            print "  levelMod          :", refr.levelMod
            formID = refr.unknownXRTMFormID
            if(formID != None):
                print "  unknownXRTMFormID : %08X" % formID
            else:
                print "  unknownXRTMFormID :", formID
            print "  actionFlags       :", refr.actionFlags
            print "  count             :", refr.count
            print "  markerFlags       :", refr.markerFlags
            print "  markerName        :", refr.markerName
            print "  markerType        :", refr.markerType
            print "  markerUnused      :", refr.markerUnused
            print "  scale             :", refr.scale
            print "  soul              :", refr.soul
            print "  posX              :", refr.posX
            print "  posY              :", refr.posY
            print "  posZ              :", refr.posZ
            print "  rotX              :", refr.rotX
            print "  rotY              :", refr.rotY
            print "  rotZ              :", refr.rotZ
            break

        pgrd = record.PGRD
        if(pgrd != None):
            print
            print "  fid    : %08X" % pgrd.fid
            print "  flags1 :", pgrd.flags1
            print "  flags2 :", pgrd.flags2

            print "  count :", pgrd.count
            print "  PGRP"
            for pgrp in pgrd.PGRP:
                print "    x           :", pgrp.x
                print "    y           :", pgrp.y
                print "    z           :", pgrp.z
                print "    connections :", pgrp.connections
                print "    unused1     :", pgrp.unused1
                break

            print "  PGAG :", pgrd.PGAG
            print "  PGRR :", pgrd.PGRR
            print "  PGRI"
            for pgri in pgrd.PGRI:
                print "    point   :", pgri.point
                print "    unused1 :", pgri.unused1
                print "    x       :", pgri.x
                print "    y       :", pgri.y
                print "    z       :", pgri.z
                break
            print "  PGRL"
            for pgrl in pgrd.PGRL:
                print "    reference : %08X" % pgrl.reference
                print "    points"
                for point in pgrl.points:
                    print "      ", point
                break
        break

    print "CELL:Create Record Test"
    newRecord = newMod.createCELLRecord()
    print "CELL:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CELLWarTest"

    newRecord.full = "WarTestCELL"
    newRecord.flags = 1
    newRecord.ambientRed = 2
    newRecord.ambientGreen = 3
    newRecord.ambientBlue = 4
    newRecord.unused1 = [1]
    newRecord.directionalRed = 5
    newRecord.directionalGreen = 6
    newRecord.directionalBlue = 7
    newRecord.unused2 = [2]
    newRecord.fogRed = 8
    newRecord.fogGreen = 9
    newRecord.fogBlue = 10
    newRecord.unused3 = [3]
    newRecord.fogNear = 11
    newRecord.fogFar = 12
    newRecord.directionalXY = 13
    newRecord.directionalZ = 14
    newRecord.directionalFade = 15
    newRecord.fogClip = 16
    newRecord.music = 1
    newRecord.owner = 7
    newRecord.rank = 1
    newRecord.globalVariable = 17
    newRecord.climate = 18
    newRecord.waterHeight = 19
    newRecord.regions = [7,8,9]
    newRecord.posX = 20
    newRecord.posY = 21
    newRecord.water = 22

    newNPCRef = newRecord.createACHRRecord()

    newNPCRef.eid = "WarACHRTest"
    newNPCRef.base = 7
    newNPCRef.unknownXPCIFormID = 14
    newNPCRef.unknownXPCIString = "Hrm?"
    newNPCRef.lod1 = 10.1
    newNPCRef.lod2 = 11.2
    newNPCRef.lod3 = 12.3
    newNPCRef.parent = 7
    newNPCRef.parentFlags = 1
    newNPCRef.unused1 = [1,2,3]
    newNPCRef.merchantContainer = 18
    newNPCRef.horse = 19
    newNPCRef.xrgd_p = []
    newNPCRef.scale = 1.8
    newNPCRef.posX = 100
    newNPCRef.posY = 200
    newNPCRef.posZ = 300
    newNPCRef.rotX = 1
    newNPCRef.rotY = 2
    newNPCRef.rotZ = 3

    newCreaRef = newRecord.createACRERecord()

    newCreaRef.eid = "WarACRETest"
    newCreaRef.base = 7
    newCreaRef.owner = 8
    newCreaRef.rank = 1
    newCreaRef.globalVariable = 2
    newCreaRef.parent = 14
    newCreaRef.parentFlags = 1
    newCreaRef.unused1 = [1,2,3]
    newCreaRef.xrgd_p = [0x23,0xff, 0x25]
    newCreaRef.scale = 1.2
    newCreaRef.posX = 1
    newCreaRef.posY = 2
    newCreaRef.posZ = 3
    newCreaRef.rotX = 4
    newCreaRef.rotY = 5
    newCreaRef.rotZ = 6

    newObjRef = newRecord.createREFRRecord()

    newObjRef.eid = "WarREFRTest"    
    newObjRef.base = 7
    newObjRef.destinationFormID = 8
    newObjRef.destinationPosX = 1
    newObjRef.destinationPosY = 2
    newObjRef.destinationPosZ = 3
    newObjRef.destinationRotX = 4
    newObjRef.destinationRotY = 5
    newObjRef.destinationRotZ = 6
    newObjRef.lockLevel = 5
    newObjRef.unused1 = [1,2,3]
    newObjRef.lockKey = 14
    newObjRef.unused2 = [1,2,3,4]
    newObjRef.lockFlags = 1
    newObjRef.unused3 = [1,2,3]
    newObjRef.owner = 15
    newObjRef.rank = 1
    newObjRef.globalVariable = 2
    newObjRef.parent = 16
    newObjRef.parentFlags = 1
    newObjRef.unused4 = [1, 2, 3]
    newObjRef.targetFormID = 17
    newObjRef.seed = 1234
    newObjRef.lod1 = 1
    newObjRef.lod2 = 2
    newObjRef.lod3 = 3
    newObjRef.charge = 4
    newObjRef.health = 5
    newObjRef.unknownXPCIFormID = 6
    newObjRef.unknownXPCIString = "blah?"
    newObjRef.levelMod = 7
    newObjRef.unknownXRTMFormID = 8
    newObjRef.actionFlags = 1
    newObjRef.count = 10
    newObjRef.markerFlags = 1
    newObjRef.markerName = "Marker!"
    newObjRef.markerType = 1
    newObjRef.markerUnused = [1]
    newObjRef.scale = 1.2
    newObjRef.soul = 6
    newObjRef.posX = 5
    newObjRef.posY = 4
    newObjRef.posZ = 3 
    newObjRef.rotX = 2
    newObjRef.rotY = 1
    newObjRef.rotZ = 11.2
    
    newObjRef = newRecord.createREFRRecord()

    newObjRef.eid = "WarREFRTest"    
    newObjRef.base = 7
    newObjRef.destinationFormID = 8
    newObjRef.destinationPosX = 1
    newObjRef.destinationPosY = 2
    newObjRef.destinationPosZ = 3
    newObjRef.destinationRotX = 4
    newObjRef.destinationRotY = 5
    newObjRef.destinationRotZ = 6
    newObjRef.lockLevel = 5
    newObjRef.unused1 = [1,2,3]
    newObjRef.lockKey = 14
    newObjRef.unused2 = [1,2,3,4]
    newObjRef.lockFlags = 1
    newObjRef.unused3 = [1,2,3]
    newObjRef.owner = 15
    newObjRef.rank = 1
    newObjRef.globalVariable = 2
    newObjRef.parent = 16
    newObjRef.parentFlags = 1
    newObjRef.unused4 = [1, 2, 3]
    newObjRef.targetFormID = 17
    newObjRef.seedOffset = 1
    newObjRef.lod1 = 1
    newObjRef.lod2 = 2
    newObjRef.lod3 = 3
    newObjRef.charge = 4
    newObjRef.health = 5
    newObjRef.unknownXPCIFormID = 6
    newObjRef.unknownXPCIString = "blah?"
    newObjRef.levelMod = 7
    newObjRef.unknownXRTMFormID = 8
    newObjRef.actionFlags = 1
    newObjRef.count = 10
    newObjRef.markerFlags = 1
    newObjRef.markerName = "Marker!"
    newObjRef.markerType = 1
    newObjRef.markerUnused = [1]
    newObjRef.scale = 1.2
    newObjRef.soul = 6
    newObjRef.posX = 5
    newObjRef.posY = 4
    newObjRef.posZ = 3 
    newObjRef.rotX = 2
    newObjRef.rotY = 1
    newObjRef.rotZ = 11.2

    print "pathgrid..."
    newPgrd = newRecord.createPGRDRecord()
    newPgrd.count = 5
    newPgrp1 = newPgrd.newPGRPElement()
    newPgrp1.x = 1
    newPgrp1.y = 2
    newPgrp1.z = 3
    newPgrp1.connections = 4
    newPgrp2 = newPgrd.newPGRPElement()
    newPgrp2.x = 2
    newPgrp2.y = 3
    newPgrp2.z = 4
    newPgrp2.connections = 4
    newPgrp3 = newPgrd.newPGRPElement()
    newPgrp3.x = 3
    newPgrp3.y = 4
    newPgrp3.z = 5
    newPgrp3.connections = 4
    newPgrp4 = newPgrd.newPGRPElement()
    newPgrp4.x = 4
    newPgrp4.y = 5
    newPgrp4.z = 6
    newPgrp4.connections = 4
    newPgrp5 = newPgrd.newPGRPElement()
    newPgrp5.x = 5
    newPgrp5.y = 6
    newPgrp5.z = 7
    newPgrp5.connections = 4
    newPgrp6 = newPgrd.newPGRPElement()
    newPgrp6.x = 6
    newPgrp6.y = 7
    newPgrp6.z = 8
    newPgrp6.connections = 4
    newPgrd.PGRP = [newPgrp6, newPgrp1, newPgrp2, newPgrp3, newPgrp4]
##
####    newPgrd.PGAG = [0x22, 0x23, 0x01]
####    
####    newPgrd.PGRR = [0x00, 0xFF, 0x00]
##        
    newPgri1 = newPgrd.newPGRIElement()
    newPgri1.point = 1
    newPgri1.unused1 = [1,2]
    newPgri1.x = 2
    newPgri1.y = 3
    newPgri1.z = 4
    newPgri2 = newPgrd.newPGRIElement()
    newPgri2.point = 2
    newPgri2.unused1 = [1,2]
    newPgri2.x = 2
    newPgri2.y = 3
    newPgri2.z = 4
    newPgri3 = newPgrd.newPGRIElement()
    newPgri3.point = 3
    newPgri3.unused1 = [1,2]
    newPgri3.x = 2
    newPgri3.y = 3
    newPgri3.z = 4
    newPgri4 = newPgrd.newPGRIElement()
    newPgri4.point = 4
    newPgri4.unused1 = [1,2]
    newPgri4.x = 2
    newPgri4.y = 3
    newPgri4.z = 4
    newPgri5 = newPgrd.newPGRIElement()
    newPgri5.point = 5
    newPgri5.unused1 = [1,2]
    newPgri5.x = 2
    newPgri5.y = 3
    newPgri5.z = 4
    newPgri6 = newPgrd.newPGRIElement()
    newPgri6.point = 6
    newPgri6.unused1 = [1,2]
    newPgri6.x = 2
    newPgri6.y = 3
    newPgri6.z = 4
    newPgrd.PGRI = [newPgri6, newPgri1, newPgri2, newPgri3, newPgri4]

    newPgrl1 = newPgrd.newPGRLElement()
    newPgrl1.reference = 7
    newPgrl1.points = [1,2,3]
    newPgrl2 = newPgrd.newPGRLElement()
    newPgrl2.reference = 8
    newPgrl2.points = [1]
    newPgrl3 = newPgrd.newPGRLElement()
    newPgrl3.reference = 9
    newPgrl3.points = [1,2]
    newPgrl4 = newPgrd.newPGRLElement()
    newPgrl4.reference = 10
    newPgrl4.points = [1,2,3,4]
    newPgrl5 = newPgrd.newPGRLElement()
    newPgrl5.reference = 11
    newPgrl5.points = [1,2,3]
    newPgrl6 = newPgrd.newPGRLElement()
    newPgrl6.reference = 14
    newPgrl6.points = [1, 2, 3, 4, 5, 6]
    newPgrd.PGRL = [newPgrl6, newPgrl1, newPgrl2, newPgrl3, newPgrl4]

    print "CELL:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full             :", newRecord.full
    print "flags            :", newRecord.flags
    print "ambientRed       :", newRecord.ambientRed
    print "ambientGreen     :", newRecord.ambientGreen
    print "ambientBlue      :", newRecord.ambientBlue
    print "unused1          :", newRecord.unused1
    print "directionalRed   :", newRecord.directionalRed
    print "directionalGreen :", newRecord.directionalGreen
    print "directionalBlue  :", newRecord.directionalBlue
    print "unused2          :", newRecord.unused2
    print "fogRed           :", newRecord.fogRed
    print "fogGreen         :", newRecord.fogGreen
    print "fogBlue          :", newRecord.fogBlue
    print "unused3          :", newRecord.unused3
    print "fogNear          :", newRecord.fogNear
    print "fogFar           :", newRecord.fogFar
    print "directionalXY    :", newRecord.directionalXY
    print "directionalZ     :", newRecord.directionalZ
    print "directionalFade  :", newRecord.directionalFade
    print "fogClip          :", newRecord.fogClip
    print "music            :", newRecord.music
    print "owner            : %08X" % newRecord.owner
    print "rank             :", newRecord.rank
    print "globalVariable   :", newRecord.globalVariable
    print "climate          : %08X" % newRecord.climate
    print "waterHeight      :", newRecord.waterHeight
    print "regions          :", newRecord.regions
    print "posX             :", newRecord.posX
    print "posY             :", newRecord.posY
    print "water            : %08X" % newRecord.water

    print "Placed NPCs"
    for achr in newRecord.ACHR:
        print
        print "  fid    : %08X" % achr.fid
        print "  flags1 :", achr.flags1
        print "  flags2 :", achr.flags2
        print "  eid    :", achr.eid
        
        print "  base              : %08X" % achr.base
        formID = achr.unknownXPCIFormID
        if(formID != None):
            print "  unknownXPCIFormID : %08X" % formID
        else:
            print "  unknownXPCIFormID :", formID
        print "  unknownXPCIString :", achr.unknownXPCIString
        print "  lod1              :", achr.lod1
        print "  lod2              :", achr.lod2
        print "  lod3              :", achr.lod3
        print "  parent            : %08X" % achr.parent
        print "  parentFlags       :", achr.parentFlags
        print "  unused1           :", achr.unused1
        print "  merchantContainer : %08X" % achr.merchantContainer
        print "  horse             : %08X" % achr.horse
        print "  xrgd_p            :", achr.xrgd_p
        print "  scale             :", achr.scale
        print "  posX              :", achr.posX
        print "  posY              :", achr.posY
        print "  posZ              :", achr.posZ
        print "  rotX              :", achr.rotX
        print "  rotY              :", achr.rotY
        print "  rotZ              :", achr.rotZ

    print "Placed Creatures"
    for acre in newRecord.ACRE:
        print
        print "  fid    : %08X" % acre.fid
        print "  flags1 :", acre.flags1
        print "  flags2 :", acre.flags2
        print "  eid    :", acre.eid

        print "  base           : %08X" % acre.base
        formID = acre.owner
        if(formID != None):
            print "  owner          : %08X" % formID
        else:
            print "  owner          :", formID
            
        print "  rank           :", acre.rank
        formID = acre.globalVariable
        if(formID != None):
            print "  globalVariable : %08X" % formID
        else:
            print "  globalVariable :", formID
        formID = acre.parent
        if(formID != None):
            print "  parent         : %08X" % formID
        else:
            print "  parent         :", formID
        print "  parentFlags    :", acre.parentFlags
        print "  unused1        :", acre.unused1
        print "  xrgd_p         :", acre.xrgd_p
        print "  scale          :", acre.scale
        print "  posX           :", acre.posX
        print "  posY           :", acre.posY
        print "  posZ           :", acre.posZ
        print "  rotX           :", acre.rotX
        print "  rotY           :", acre.rotY
        print "  rotZ           :", acre.rotZ

    print "Placed Objects"
    for refr in newRecord.REFR:
        print
        print "  fid    : %08X" % refr.fid
        print "  flags1 :", refr.flags1
        print "  flags2 :", refr.flags2
        print "  eid    :", refr.eid
        formID = refr.base
        if(formID != None):
            print "  base              : %08X" % formID
        else:
            print "  base              :", formID
        formID = refr.destinationFormID
        if(formID != None):
            print "  destinationFormID : %08X" % formID
        else:
            print "  destinationFormID :", formID

        print "  destinationPosX   :", refr.destinationPosX
        print "  destinationPosY   :", refr.destinationPosY
        print "  destinationPosZ   :", refr.destinationPosZ
        print "  destinationRotX   :", refr.destinationRotX
        print "  destinationRotY   :", refr.destinationRotY
        print "  destinationRotZ   :", refr.destinationRotZ
        print "  lockLevel         :", refr.lockLevel
        print "  unused1           :", refr.unused1

        formID = refr.lockKey
        if(formID != None):
            print "  lockKey           : %08X" % formID
        else:
            print "  lockKey           :", formID

        print "  unused2           :", refr.unused2
        print "  lockFlags         :", refr.lockFlags
        print "  unused3           :", refr.unused3
        formID = refr.owner
        if(formID != None):
            print "  owner             : %08X" % formID
        else:
            print "  owner             :", formID
            
        print "  rank              :", refr.rank
        formID = refr.globalVariable
        if(formID != None):
            print "  globalVariable    : %08X" % formID
        else:
            print "  globalVariable    :", formID
        formID = refr.parent
        if(formID != None):
            print "  parent            : %08X" % formID
        else:
            print "  parent            :", formID
        print "  parentFlags       :", refr.parentFlags
        print "  unused4           :", refr.unused4
        formID = refr.targetFormID
        if(formID != None):
            print "  targetFormID      : %08X" % formID
        else:
            print "  targetFormID      :", formID
        print "  seed              :", refr.seed
        print "  seedOffset        :", refr.seedOffset
        print "  lod1              :", refr.lod1
        print "  lod2              :", refr.lod2
        print "  lod3              :", refr.lod3
        print "  charge            :", refr.charge
        print "  health            :", refr.health
        formID = refr.unknownXPCIFormID
        if(formID != None):
            print "  unknownXPCIFormID : %08X" % formID
        else:
            print "  unknownXPCIFormID :", formID
        print "  unknownXPCIString :", refr.unknownXPCIString
        print "  levelMod          :", refr.levelMod
        formID = refr.unknownXRTMFormID
        if(formID != None):
            print "  unknownXRTMFormID : %08X" % formID
        else:
            print "  unknownXRTMFormID :", formID
        print "  actionFlags       :", refr.actionFlags
        print "  count             :", refr.count
        print "  markerFlags       :", refr.markerFlags
        print "  markerName        :", refr.markerName
        print "  markerType        :", refr.markerType
        print "  markerUnused      :", refr.markerUnused
        print "  scale             :", refr.scale
        print "  soul              :", refr.soul
        print "  posX              :", refr.posX
        print "  posY              :", refr.posY
        print "  posZ              :", refr.posZ
        print "  rotX              :", refr.rotX
        print "  rotY              :", refr.rotY
        print "  rotZ              :", refr.rotZ

    print "Pathgrid"
    pgrd = newRecord.PGRD
    if(pgrd != None):
        print
        print "  fid    : %08X" % pgrd.fid
        print "  flags1 :", pgrd.flags1
        print "  flags2 :", pgrd.flags2

        print "  count :", pgrd.count
        print "  PGRP"
        for pgrp in pgrd.PGRP:
            print "    x           :", pgrp.x
            print "    y           :", pgrp.y
            print "    z           :", pgrp.z
            print "    connections :", pgrp.connections
            print "    unused1     :", pgrp.unused1
            break

        print "  PGAG :", pgrd.PGAG
        print "  PGRR :", pgrd.PGRR
        print "  PGRI"
        for pgri in pgrd.PGRI:
            print "    point   :", pgri.point
            print "    unused1 :", pgri.unused1
            print "    x       :", pgri.x
            print "    y       :", pgri.y
            print "    z       :", pgri.z
            break
        print "  PGRL"
        for pgrl in pgrd.PGRL:
            print "    reference : %08X" % pgrl.reference
            print "    points"
            for point in pgrl.points:
                print "      ", point
            break
    print "CELL:CopyAsOverride Test"
    for record in Current[0].CELL:
        trgCell = record.CopyAsOverride(newMod)
        for npcRef in record.ACHR:
            npcRef.CopyAsOverride(trgCell)
        for creaRef in record.ACRE:
            creaRef.CopyAsOverride(trgCell)
        for objRef in record.REFR:
            objRef.CopyAsOverride(trgCell)
        Pgrd = record.PGRD
        if(Pgrd): Pgrd.CopyAsOverride(trgCell)

    print "CELL:CopyAsNew Test"
    for record in Current[0].CELL:
        trgCell = record.CopyAsNew(newMod)
        for npcRef in record.ACHR:
            npcRef.CopyAsNew(trgCell)
        for creaRef in record.ACRE:
            creaRef.CopyAsNew(trgCell)
        for objRef in record.REFR:
            objRef.CopyAsNew(trgCell)
        Pgrd = record.PGRD
        if(Pgrd): Pgrd.CopyAsNew(trgCell)

    print "CELL:Save Test - TestCELL.esp"
    newMod.safeSave()
    print "CELL:Finished testing"
    
def TestWRLD():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestWRLD.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current[0].WRLD:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

   
        print "full      :", record.full
        formID = record.parent
        if(formID != None):
            print "parent    : %08X" % formID
        else:
            print "parent    :", formID
        formID = record.climate
        if(formID != None):
            print "climate   : %08X" % formID
        else:
            print "climate   :", formID
        formID = record.water
        if(formID != None):
            print "water     : %08X" % formID
        else:
            print "water     :", formID
        print "mapPath   :", record.mapPath
        print "dimX      :", record.dimX
        print "dimY      :", record.dimY
        print "NWCellX   :", record.NWCellX
        print "NWCellY   :", record.NWCellY
        print "SECellX   :", record.SECellX
        print "SECellY   :", record.SECellY
        print "flags     :", record.flags
        print "unknown00 :", record.unknown00
        print "unknown01 :", record.unknown01
        print "unknown90 :", record.unknown90
        print "unknown91 :", record.unknown91
        print "sound     :", record.sound
##        print "ofst_p    :", record.ofst_p
        for wrldCell in record.CELLS:
            print
            print "fid     : %08X" % wrldCell.fid
            print "flags1  :", wrldCell.flags1
            print "flags2  :", wrldCell.flags2
            print "eid     :", wrldCell.eid

            print "full             :", wrldCell.full
            print "flags            :", wrldCell.flags
            print "ambientRed       :", wrldCell.ambientRed
            print "ambientGreen     :", wrldCell.ambientGreen
            print "ambientBlue      :", wrldCell.ambientBlue
            print "unused1          :", wrldCell.unused1
            print "directionalRed   :", wrldCell.directionalRed
            print "directionalGreen :", wrldCell.directionalGreen
            print "directionalBlue  :", wrldCell.directionalBlue
            print "unused2          :", wrldCell.unused2
            print "fogRed           :", wrldCell.fogRed
            print "fogGreen         :", wrldCell.fogGreen
            print "fogBlue          :", wrldCell.fogBlue
            print "unused3          :", wrldCell.unused3
            print "fogNear          :", wrldCell.fogNear
            print "fogFar           :", wrldCell.fogFar
            print "directionalXY    :", wrldCell.directionalXY
            print "directionalZ     :", wrldCell.directionalZ
            print "directionalFade  :", wrldCell.directionalFade
            print "fogClip          :", wrldCell.fogClip
            print "music            :", wrldCell.music
            formID = wrldCell.owner
            if(formID != None):
                print "owner            : %08X" % formID
            else:
                print "owner            :", formID
                
            print "rank             :", wrldCell.rank
            formID = wrldCell.globalVariable
            if(formID != None):
                print "globalVariable   : %08X" % formID
            else:
                print "globalVariable   :", formID        
            print "climate          : %08X" % wrldCell.climate
            print "waterHeight      :", wrldCell.waterHeight
            print "regions          :", wrldCell.regions
            print "posX             :", wrldCell.posX
            print "posY             :", wrldCell.posY
            print "water            : %08X" % wrldCell.water

            print "Placed NPCs"
            for achr in wrldCell.ACHR:
                print
                print "  fid    : %08X" % achr.fid
                print "  flags1 :", achr.flags1
                print "  flags2 :", achr.flags2
                print "  eid    :", achr.eid
                
                print "  base              : %08X" % achr.base
                formID = achr.unknownXPCIFormID
                if(formID != None):
                    print "  unknownXPCIFormID : %08X" % formID
                else:
                    print "  unknownXPCIFormID :", formID
                print "  unknownXPCIString :", achr.unknownXPCIString
                print "  lod1              :", achr.lod1
                print "  lod2              :", achr.lod2
                print "  lod3              :", achr.lod3
                formID = achr.parent
                if(formID != None):
                    print "  parent            : %08X" % formID
                else:
                    print "  parent            :", formID
                print "  parentFlags       :", achr.parentFlags
                print "  unused1           :", achr.unused1
                formID = achr.merchantContainer
                if(formID != None):
                    print "  merchantContainer : %08X" % formID
                else:
                    print "  merchantContainer :", formID
                formID = achr.horse
                if(formID != None):
                    print "  horse             : %08X" % formID
                else:
                    print "  horse             :", formID
                print "  xrgd_p            :", achr.xrgd_p
                print "  scale             :", achr.scale
                print "  posX              :", achr.posX
                print "  posY              :", achr.posY
                print "  posZ              :", achr.posZ
                print "  rotX              :", achr.rotX
                print "  rotY              :", achr.rotY
                print "  rotZ              :", achr.rotZ
                break

            print "Placed Creatures"
            for acre in wrldCell.ACRE:
                print
                print "  fid    : %08X" % acre.fid
                print "  flags1 :", acre.flags1
                print "  flags2 :", acre.flags2
                print "  eid    :", acre.eid

                print "  base           : %08X" % acre.base
                formID = acre.owner
                if(formID != None):
                    print "  owner          : %08X" % formID
                else:
                    print "  owner          :", formID
                    
                print "  rank           :", acre.rank
                formID = acre.globalVariable
                if(formID != None):
                    print "  globalVariable : %08X" % formID
                else:
                    print "  globalVariable :", formID
                formID = acre.parent
                if(formID != None):
                    print "  parent         : %08X" % formID
                else:
                    print "  parent         :", formID
                print "  parentFlags    :", acre.parentFlags
                print "  unused1        :", acre.unused1
                print "  xrgd_p         :", acre.xrgd_p
                print "  scale          :", acre.scale
                print "  posX           :", acre.posX
                print "  posY           :", acre.posY
                print "  posZ           :", acre.posZ
                print "  rotX           :", acre.rotX
                print "  rotY           :", acre.rotY
                print "  rotZ           :", acre.rotZ
                break

            print "Placed Objects"
            for refr in wrldCell.REFR:
                print
                print "  fid    : %08X" % refr.fid
                print "  flags1 :", refr.flags1
                print "  flags2 :", refr.flags2
                print "  eid    :", refr.eid
                formID = refr.base
                if(formID != None):
                    print "  base              : %08X" % formID
                else:
                    print "  base              :", formID
                formID = refr.destinationFormID
                if(formID != None):
                    print "  destinationFormID : %08X" % formID
                else:
                    print "  destinationFormID :", formID

                print "  destinationPosX   :", refr.destinationPosX
                print "  destinationPosY   :", refr.destinationPosY
                print "  destinationPosZ   :", refr.destinationPosZ
                print "  destinationRotX   :", refr.destinationRotX
                print "  destinationRotY   :", refr.destinationRotY
                print "  destinationRotZ   :", refr.destinationRotZ
                print "  lockLevel         :", refr.lockLevel
                print "  unused1           :", refr.unused1

                formID = refr.lockKey
                if(formID != None):
                    print "  lockKey           : %08X" % formID
                else:
                    print "  lockKey           :", formID

                print "  unused2           :", refr.unused2
                print "  lockFlags         :", refr.lockFlags
                print "  unused3           :", refr.unused3
                formID = refr.owner
                if(formID != None):
                    print "  owner             : %08X" % formID
                else:
                    print "  owner             :", formID
                    
                print "  rank              :", refr.rank
                formID = refr.globalVariable
                if(formID != None):
                    print "  globalVariable    : %08X" % formID
                else:
                    print "  globalVariable    :", formID
                formID = refr.parent
                if(formID != None):
                    print "  parent            : %08X" % formID
                else:
                    print "  parent            :", formID
                print "  parentFlags       :", refr.parentFlags
                print "  unused4           :", refr.unused4
                formID = refr.targetFormID
                if(formID != None):
                    print "  targetFormID      : %08X" % formID
                else:
                    print "  targetFormID      :", formID
                print "  seed              :", refr.seed
                print "  seedOffset        :", refr.seedOffset
                print "  lod1              :", refr.lod1
                print "  lod2              :", refr.lod2
                print "  lod3              :", refr.lod3
                print "  charge            :", refr.charge
                print "  health            :", refr.health
                formID = refr.unknownXPCIFormID
                if(formID != None):
                    print "  unknownXPCIFormID : %08X" % formID
                else:
                    print "  unknownXPCIFormID :", formID
                print "  unknownXPCIString :", refr.unknownXPCIString
                print "  levelMod          :", refr.levelMod
                formID = refr.unknownXRTMFormID
                if(formID != None):
                    print "  unknownXRTMFormID : %08X" % formID
                else:
                    print "  unknownXRTMFormID :", formID
                print "  actionFlags       :", refr.actionFlags
                print "  count             :", refr.count
                print "  markerFlags       :", refr.markerFlags
                print "  markerName        :", refr.markerName
                print "  markerType        :", refr.markerType
                print "  markerUnused      :", refr.markerUnused
                print "  scale             :", refr.scale
                print "  soul              :", refr.soul
                print "  posX              :", refr.posX
                print "  posY              :", refr.posY
                print "  posZ              :", refr.posZ
                print "  rotX              :", refr.rotX
                print "  rotY              :", refr.rotY
                print "  rotZ              :", refr.rotZ
                break

            pgrd = wrldCell.PGRD
            if(pgrd != None):
                print
                print "  PGRD"
                print "  fid    : %08X" % pgrd.fid
                print "  flags1 :", pgrd.flags1
                print "  flags2 :", pgrd.flags2

                print "  count :", pgrd.count
                print "  PGRP"
                for pgrp in pgrd.PGRP:
                    print "    x           :", pgrp.x
                    print "    y           :", pgrp.y
                    print "    z           :", pgrp.z
                    print "    connections :", pgrp.connections
                    print "    unused1     :", pgrp.unused1
                    break

                print "  PGAG :", pgrd.PGAG
                print "  PGRR :", pgrd.PGRR
                print "  PGRI"
                for pgri in pgrd.PGRI:
                    print "    point   :", pgri.point
                    print "    unused1 :", pgri.unused1
                    print "    x       :", pgri.x
                    print "    y       :", pgri.y
                    print "    z       :", pgri.z
                    break
                print "  PGRL"
                for pgrl in pgrd.PGRL:
                    print "    reference : %08X" % pgrl.reference
                    print "    points"
                    for point in pgrl.points:
                        print "      ", point
                    break
            cLand = wrldCell.LAND
            if(cLand != None):
                print
                print "  LAND"
                print "  fid    : %08X" % cLand.fid
                print "  flags1 :", cLand.flags1
                print "  flags2 :", cLand.flags2


                print "  data         :", cLand.data
                print "  normals"
                for cRow in cLand.normals:
                    for cColumn in cRow:
                        print "    Co-ords : ", cColumn._listIndex, ",", cColumn._listX2Index
                        print "        x   :", cColumn.x
                        print "        y   :", cColumn.y
                        print "        z   :", cColumn.z
                        print
                print "  heightOffset :", cLand.heightOffset
                print "  heights"
                for cRow in cLand.heights:
                    for cColumn in cRow:
                        print "    Co-ords    : ", cColumn._listIndex, ",", cColumn._listX2Index
                        print "        height :", cColumn.height
                        print
                print "  unused1      :", cLand.unused1
                print "  colors"
                for cRow in cLand.colors:
                    for cColumn in cRow:
                        print "    Co-ords   : ", cColumn._listIndex, ",", cColumn._listX2Index
                        print "        red   :", cColumn.red
                        print "        green :", cColumn.green
                        print "        blue  :", cColumn.blue
                        print
                print "  baseTextures"
                for baseTexture in cLand.baseTextures:
                    print "    texture  : %08X" % baseTexture.texture
                    print "    quadrant :", baseTexture.quadrant
                    print "    unused1  :", baseTexture.unused1
                    print "    layer    :", baseTexture.layer
                    print
                print "  alphaLayers"
                for alphaLayer in cLand.alphaLayers:
                    print "    texture  : %08X" % alphaLayer.texture
                    print "    quadrant :", alphaLayer.quadrant
                    print "    unused1  :", alphaLayer.unused1
                    print "    layer    :", alphaLayer.layer
                    print "    opacities"
                    for cOpacity in alphaLayer.opacities:
                        print "      position :", cOpacity.position
                        print "      unused1  :", cOpacity.unused1
                        print "      opacity  :", cOpacity.opacity
                        print
                    print
                print "  vertexTextures"
                for vertexTexture in cLand.vertexTextures:
                    print "    texture  : %08X" % vertexTexture.texture
                    print

                print "  Position"
                for cRow in cLand.Position:
                    for cColumn in cRow:
                        print "    Co-ords row:", cColumn._listIndex, ", col:", cColumn._listX2Index
                        print "        height        :", cColumn.height
                        print "        normalX       :", cColumn.normalX
                        print "        normalY       :", cColumn.normalY
                        print "        normalZ       :", cColumn.normalZ
                        print "        red           :", cColumn.red
                        print "        green         :", cColumn.green
                        print "        blue          :", cColumn.blue
                        formID = cColumn.baseTexture
                        if(formID != None):
                            print "        baseTexture   : %08X" % formID
                        else:
                            print "        baseTexture   :", formID
                            
                        formID = cColumn.layer1Texture
                        if(formID != None):
                            print "        layer1Texture : %08X" % formID
                        else:
                            print "        layer1Texture :", formID
                        print "        layer1Opacity :", cColumn.layer1Opacity
                        
                        formID = cColumn.layer2Texture
                        if(formID != None):
                            print "        layer2Texture : %08X" % formID
                        else:
                            print "        layer2Texture :", formID
                        print "        layer2Opacity :", cColumn.layer2Opacity
                       
                        formID = cColumn.layer3Texture
                        if(formID != None):
                            print "        layer3Texture : %08X" % formID
                        else:
                            print "        layer3Texture :", formID
                        print "        layer3Opacity :", cColumn.layer3Opacity
                        
                        formID = cColumn.layer4Texture
                        if(formID != None):
                            print "        layer4Texture : %08X" % formID
                        else:
                            print "        layer4Texture :", formID
                        print "        layer4Opacity :", cColumn.layer4Opacity
                        
                        formID = cColumn.layer5Texture
                        if(formID != None):
                            print "        layer5Texture : %08X" % formID
                        else:
                            print "        layer5Texture :", formID
                        print "        layer5Opacity :", cColumn.layer5Opacity
                        
                        formID = cColumn.layer6Texture
                        if(formID != None):
                            print "        layer6Texture : %08X" % formID
                        else:
                            print "        layer6Texture :", formID
                        print "        layer6Opacity :", cColumn.layer6Opacity
                        
                        formID = cColumn.layer7Texture
                        if(formID != None):
                            print "        layer7Texture : %08X" % formID
                        else:
                            print "        layer7Texture :", formID
                        print "        layer7Opacity :", cColumn.layer7Opacity
                        
                        formID = cColumn.layer8Texture
                        if(formID != None):
                            print "        layer8Texture : %08X" % formID
                        else:
                            print "        layer8Texture :", formID
                        print "        layer8Opacity :", cColumn.layer8Opacity
                        print
                        
            break
        break

    print "WRLD:Create Record Test"
    newRecord = newMod.createWRLDRecord()
    print "WRLD:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WRLDWarTest"

    newRecord.full =  "TestWarWorld"
    newRecord.parent = 7
    newRecord.climate = 8
    newRecord.water = 9
    newRecord.mapPath = r"MapTest\Path\Destination\test.dds"
    newRecord.dimX = 10
    newRecord.dimY = 11
    newRecord.NWCellX = 12
    newRecord.NWCellY = 13
    newRecord.SECellX = 14
    newRecord.SECellY = 15
    newRecord.flags = 1
    newRecord.unknown00 = 16
    newRecord.unknown01 = 17
    newRecord.unknown90 = 18
    newRecord.unknown91 = 19
    newRecord.sound = 20
    newRecord.ofst_p = [1,2,3,4,5,6,7,8,9,10] 

    print "WRLD:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full      :", newRecord.full
    print "parent    : %08X" % newRecord.parent
    print "climate   : %08X" % newRecord.climate
    print "water     : %08X" % newRecord.water
    print "mapPath   :", newRecord.mapPath
    print "dimX      :", newRecord.dimX
    print "dimY      :", newRecord.dimY
    print "NWCellX   :", newRecord.NWCellX
    print "NWCellY   :", newRecord.NWCellY
    print "SECellX   :", newRecord.SECellX
    print "SECellY   :", newRecord.SECellY
    print "flags     :", newRecord.flags
    print "unknown00 :", newRecord.unknown00
    print "unknown01 :", newRecord.unknown01
    print "unknown90 :", newRecord.unknown90
    print "unknown91 :", newRecord.unknown91
    print "sound     :", newRecord.sound
    print "ofst_p    :", newRecord.ofst_p    

    print "WRLD:CopyAsOverride Test"
    for record in Current[0].WRLD:
        trgWrld = record.CopyAsOverride(newMod)
        road = record.ROAD
        if(road != None): road.CopyAsOverride(trgWrld)
        for wrldCell in record.CELLS:
            trgCell = wrldCell.CopyAsOverride(trgWrld)
            cLand = wrldCell.LAND
            if(cLand):
                cLand.CopyAsOverride(trgCell)
            for npcRef in wrldCell.ACHR:
                npcRef.CopyAsOverride(trgCell)
            for creaRef in wrldCell.ACRE:
                creaRef.CopyAsOverride(trgCell)
            for objRef in wrldCell.REFR:
                objRef.CopyAsOverride(trgCell)
            Pgrd = wrldCell.PGRD
            if(Pgrd): Pgrd.CopyAsOverride(trgCell)
        

    print "WRLD:CopyAsNew Test"
    for record in Current[0].WRLD:
        trgWrld = record.CopyAsNew(newMod)
        road = record.ROAD
        if(road != None): road.CopyAsNew(trgWrld)
        for wrldCell in record.CELLS:
            cLand = wrldCell.LAND
            if(cLand):
                trgCell = wrldCell.CopyAsNew(trgWrld)
                cLand.CopyAsNew(trgCell)
            for npcRef in wrldCell.ACHR:
                npcRef.CopyAsNew(trgCell)
            for creaRef in wrldCell.ACRE:
                creaRef.CopyAsNew(trgCell)
            for objRef in wrldCell.REFR:
                objRef.CopyAsNew(trgCell)
            Pgrd = wrldCell.PGRD
            if(Pgrd): Pgrd.CopyAsNew(trgCell)

    print "WRLD:Save Test - TestWRLD.esp"
    newMod.safeSave()
    print "WRLD:Finished testing"
    
def TestDIAL():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestDIAL.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.DIAL:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "quests"
        for quest in record.quests:
            print "  %08X" % quest
        print "full     :", record.full
        print "dialType :", record.dialType

        print "infos"
        for info in record.INFO:
            print
            print "  fid    : %08X" % info.fid
            print "  flags1 :", info.flags1
            print "  flags2 :", info.flags2            
            print "  dialType     :", info.dialType
            print "  flags        :", info.flags
            print "  unused1      :", info.unused1
            print "  quest        : %08X" % info.quest
            print "  topic        : %08X" % info.topic
            print "  prevInfo     : %08X" % info.prevInfo
            print "  addTopics"
            for topic in info.addTopics:
                print "    %08X" % topic
            
            print "  responses"
            for response in info.responses:
                print "    emotionType  :", response.emotionType
                print "    emotionValue :", response.emotionValue
                print "    unused1      :", response.unused1
                print "    responseNum  :", response.responseNum
                print "    unused2      :", response.unused2
                print "    responseText :", response.responseText
                print "    actorNotes   :", response.actorNotes
                print
                
            print "  conditions"
            for condition in info.conditions:
                print "    operType  :", condition.operType
                print "    unused1   :", condition.unused1
                print "    compValue :", condition.compValue
                print "    ifunc     :", condition.ifunc
                print "    param1    :", condition.param1
                print "    param2    :", condition.param2
                print "    unused2   :", condition.unused2
                print
            
            print "  choices"
            for choice in info.choices:
                print "    %08X" % choice
                
            print "  linksFrom"
            for linksFrom in info.linksFrom:
                print "    %08X" % linksFrom
                
            print "  unused2      :", info.unused2
            print "  numRefs      :", info.numRefs
            print "  compiledSize :", info.compiledSize
            print "  lastIndex    :", info.lastIndex
            print "  scriptType   :", info.scriptType
            print "  compiled_p   :", info.compiled_p
            print "  scriptText   :", info.scriptText
            
            print "  references"
            for reference in info.references:
                if(reference.isSCRO):
                    print "    SCRO: %08X" % reference.reference
                else:
                    print "    SCRV:", reference.reference
        break
    
    print "DIAL:Create Record Test"
    newRecord = newMod.createDIALRecord()
    print "DIAL:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "DIALWarTest"
    
    newRecord.quests = [0xFF000121, 0xFE000222]    
    print "full..."
    newRecord.full = "Fancy DIAL"
    newRecord.dialType = 1

    print "INFO:Set Test"
    newInfo = newRecord.createINFORecord()
    newInfo.flags1 = 0x0102
    newInfo.flags2 = 0x0201

    newInfo.dialType = 1
    newInfo.flags = 2
    newInfo.unused1 = [1]
    newInfo.quest = 7
    newInfo.topic = 10
    newInfo.prevInfo = 15
    newInfo.addTopics = [7,15,22]

    newResponse = newInfo.newResponsesElement()
    newResponse.emotionType = 1
    newResponse.emotionValue = 2
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 3
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "RARGH!...1..oops"
    newResponse.actorNotes = "Say it with all your might!"
    
    newResponse = newInfo.newResponsesElement()
    newResponse.emotionType = 4
    newResponse.emotionValue = 5
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 6
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "RARGH!...2..oops"
    newResponse.actorNotes = "Say it with all your might!"
    
    newResponse = newInfo.newResponsesElement()    
    newResponse.emotionType = 7
    newResponse.emotionValue = 8
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 9
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "RARGH!...3..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newInfo.responses = [newInfo.responses[2], newInfo.responses[0], newInfo.responses[0], newInfo.responses[2]]    
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 4
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 5
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 6
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newInfo.conditions = [newInfo.conditions[3], newInfo.conditions[1], newInfo.conditions[0]]

    newInfo.choices = [0x0A, 0x0B, 0x0C]    
    
    newInfo.linksFrom = [0x0D, 0x0E, 0x0F]    

        
    newInfo.unused2 = [2,3,4,5]
    newInfo.numRefs = 15
    newInfo.compiledSize = 3
    newInfo.lastIndex = 4
    newInfo.scriptType = 1
    newInfo.compiled_p = [1,67,255]
    newInfo.scriptText = "scn DummyScript\nThis won't compile"

    newReference = newInfo.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True
    newReference = newInfo.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    newReference = newInfo.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = 1
    newReference = newInfo.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO =0

    newInfo.references = [newInfo.references[3], newInfo.references[1], newInfo.references[0]]

    print "INFO:Set Test"
    newInfo = newRecord.createINFORecord()
    newInfo.flags1 = 0x0102
    newInfo.flags2 = 0x0201

    newInfo.dialType = 1
    newInfo.flags = 2
    newInfo.unused1 = [1]
    newInfo.quest = 7
    newInfo.topic = 10
    newInfo.prevInfo = 15
    newInfo.addTopics = [7,15,22]

    newResponse = newInfo.newResponsesElement()
    newResponse.emotionType = 1
    newResponse.emotionValue = 2
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 3
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "1RARGH!...1..oops"
    newResponse.actorNotes = "Say it with all your might!"
    
    newResponse = newInfo.newResponsesElement()
    newResponse.emotionType = 4
    newResponse.emotionValue = 5
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 6
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "1RARGH!...2..oops"
    newResponse.actorNotes = "Say it with all your might!"
    
    newResponse = newInfo.newResponsesElement()    
    newResponse.emotionType = 7
    newResponse.emotionValue = 8
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 9
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "1RARGH!...3..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newInfo.responses = [newInfo.responses[2], newInfo.responses[0], newInfo.responses[0], newInfo.responses[2]]   
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 4
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 5
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 6
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newInfo.conditions = [newInfo.conditions[3], newInfo.conditions[1], newInfo.conditions[0]]

    newInfo.choices = [0x0A, 0x0B, 0x0C]    
    
    newInfo.linksFrom = [0x0D, 0x0E, 0x0F]

    print "INFO:Set Test"
    newInfo = newRecord.createINFORecord()
    newInfo.flags1 = 0x0102
    newInfo.flags2 = 0x0201

    newInfo.dialType = 1
    newInfo.flags = 2
    newInfo.unused1 = [1]
    newInfo.quest = 7
    newInfo.topic = 10
    newInfo.prevInfo = 15
    newInfo.addTopics = [7,15,22]

    newResponse = newInfo.newResponsesElement()
    newResponse.emotionType = 1
    newResponse.emotionValue = 2
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 3
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "2RARGH!...1..oops"
    newResponse.actorNotes = "Say it with all your might!"
    
    newResponse = newInfo.newResponsesElement()
    newResponse.emotionType = 4
    newResponse.emotionValue = 5
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 6
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "2RARGH!...2..oops"
    newResponse.actorNotes = "Say it with all your might!"
    
    newResponse = newInfo.newResponsesElement()    
    newResponse.emotionType = 7
    newResponse.emotionValue = 8
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 9
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "2RARGH!...3..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newInfo.responses = [newInfo.responses[2], newInfo.responses[0], newInfo.responses[0], newInfo.responses[2]]  
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 4
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 5
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 6
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newInfo.newConditionsElement()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newInfo.conditions = [newInfo.conditions[3], newInfo.conditions[1], newInfo.conditions[0]]

    newInfo.choices = [0x0A, 0x0B, 0x0C]    
    
    newInfo.linksFrom = [0x0D, 0x0E, 0x0F]    

        
    newInfo.unused2 = [2,3,4,5]
    newInfo.numRefs = 15
    newInfo.compiledSize = 3
    newInfo.lastIndex = 4
    newInfo.scriptType = 1
    newInfo.compiled_p = [1,67,255]
    newInfo.scriptText = "scn DummyScript\nThis won't compile"

    newReference = newInfo.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True
    newReference = newInfo.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    newReference = newInfo.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = 1
    newReference = newInfo.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO =0

    newInfo.references = [newInfo.references[3], newInfo.references[1], newInfo.references[0]]    
        
    print "DIAL:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    
    print "quests"
    for quest in newRecord.quests:
        print "  %08X" % quest
    print "full     :", newRecord.full
    print "dialType :", newRecord.dialType

    print "infos"
    for info in newRecord.INFO:
        print
        print "  fid    : %08X" % info.fid
        print "  flags1 :", info.flags1
        print "  flags2 :", info.flags2
        
        print "  dialType     :", info.dialType
        print "  flags        :", info.flags
        print "  unused1      :", info.unused1
        print "  quest        : %08X" % info.quest
        print "  topic        : %08X" % info.topic
        print "  prevInfo     : %08X" % info.prevInfo
        print "  addTopics"
        for topic in info.addTopics:
            print "    %08X" % topic
        
        print "  responses"
        for response in info.responses:
            print "    emotionType  :", response.emotionType
            print "    emotionValue :", response.emotionValue
            print "    unused1      :", response.unused1
            print "    responseNum  :", response.responseNum
            print "    unused2      :", response.unused2
            print "    responseText :", response.responseText
            print "    actorNotes   :", response.actorNotes
            print
            
        print "  conditions"
        for condition in info.conditions:
            print "    operType  :", condition.operType
            print "    unused1   :", condition.unused1
            print "    compValue :", condition.compValue
            print "    ifunc     :", condition.ifunc
            print "    param1    :", condition.param1
            print "    param2    :", condition.param2
            print "    unused2   :", condition.unused2
            print
        
        print "  choices"
        for choice in info.choices:
            print "    %08X" % choice
            
        print "  linksFrom"
        for linksFrom in info.linksFrom:
            print "    %08X" % linksFrom
            
        print "  unused2      :", info.unused2
        print "  numRefs      :", info.numRefs
        print "  compiledSize :", info.compiledSize
        print "  lastIndex    :", info.lastIndex
        print "  scriptType   :", info.scriptType
        print "  compiled_p   :", info.compiled_p
        print "  scriptText   :", info.scriptText
        
        print "  references"
        for reference in info.references:
            if(reference.isSCRO):
                print "    SCRO: %08X" % reference.reference
            else:
                print "    SCRV:", reference.reference
    
    print "DIAL:CopyAsOverride Test"
    for record in Current[0].DIAL:
        newRecord = record.CopyAsOverride(newMod)
        for info in record.INFO:
            info.CopyAsOverride(newRecord)


    print "DIAL:CopyAsNew Test"
    for record in Current[0].DIAL:
        newRecord = record.CopyAsNew(newMod)
        for info in record.INFO:
            info.CopyAsNew(newRecord)

    print "DIAL:Save Test - TestDIAL.esp"
    newMod.safeSave()
    print "DIAL:Finished testing"

def TestQUST():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestQUST.esp", True)
    Current.minimalLoad(LoadMasters=True)

    x = 0
    for record in Current.QUST:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "script     : %08X" % record.script
        print "full       :", record.full
        print "iconPath   :", record.iconPath
        print "flags      :", record.flags
        print "priority   :", record.priority
        
        print "conditions"
        for condition in record.conditions:
            print "  operType  :", condition.operType
            print "  unused1   :", condition.unused1
            print "  compValue :", condition.compValue
            print "  ifunc     :", condition.ifunc
            print "  param1    :", condition.param1
            print "  param2    :", condition.param2
            print "  unused2   :", condition.unused2
            print
            if(x == 0):
                x = 1
        print "stages"
        for stage in record.stages:
            if(x == 1):
                x = 2
            print "  stage :", stage.stage
            print "  entries"
            for entry in stage.entries:
                if(x == 2):
                    x = 3
                print "    flags        :", entry.flags
                print "    conditions"
                for condition in entry.conditions:
                    print "      operType  :", condition.operType
                    print "      unused1   :", condition.unused1
                    print "      compValue :", condition.compValue
                    print "      ifunc     :", condition.ifunc
                    print "      param1    :", condition.param1
                    print "      param2    :", condition.param2
                    print "      unused2   :", condition.unused2
                    print
                    if(x == 3):
                        x = 4
                print "    text         :", entry.text
                print "    unused1      :", entry.unused1
                print "    numRefs      :", entry.numRefs
                print "    compiledSize :", entry.compiledSize
                print "    lastIndex    :", entry.lastIndex
                print "    scriptType   :", entry.scriptType
                print "    compiled_p   :", entry.compiled_p
                print "    scriptText   :", entry.scriptText
                print "    references"
                for reference in entry.references:
                    if(reference.isSCRO):
                        print "      SCRO: %08X" % reference.reference
                    else:
                        print "      SCRV:", reference.reference
                    if(x == 4):
                        x = 5
                print
            print
        print "targets"
        for target in record.targets:
            if(x == 5):
                x = 6
            print "  targetId : %08X" % target.targetId
            print "  flags    :", target.flags
            print "  unused1  :", target.unused1
            print "  conditions"
            for condition in target.conditions:
                print "    operType  :", condition.operType
                print "    unused1   :", condition.unused1
                print "    compValue :", condition.compValue
                print "    ifunc     :", condition.ifunc
                print "    param1    :", condition.param1
                print "    param2    :", condition.param2
                print "    unused2   :", condition.unused2
                print
                if(x == 6):
                    x = 7
        if(x == 7):
            break


    print "QUST:Create Record Test"
    newRecord = newMod.createQUSTRecord()
    print "QUST:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "QUSTWarTest"

    newRecord.script = 7
    newRecord.full = "Waruddar's Quest Test"
    newRecord.iconPath = r"QUST\Icon\Path\Test.dds"
    newRecord.flags = 1
    newRecord.priority = 2

    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 4
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 5
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 6
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newRecord.conditions = [newRecord.conditions[3], newRecord.conditions[1], newRecord.conditions[0]]

    newStage = newRecord.newStagesElement()
    newStage.stage = 10
    newEntry = newStage.newEntriesElement()
    newEntry.flags = 1
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 8
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 9
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "10How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "10Another futile attempt at making this thing work"
    newReference = newEntry.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO = True

    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]    

    newEntry = newStage.newEntriesElement()
    newEntry.flags = 1
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 7
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "20How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "20Another futile attempt at making this thing work"
    newReference = newEntry.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO = True

    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newEntry = newStage.newEntriesElement()
    newEntry.flags = 1
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 7
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "30How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "30Another futile attempt at making this thing work"
    newReference = newEntry.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO = True

    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]  

    newStage.entries = [newStage.entries[2], newStage.entries[0]]

    newStage = newRecord.newStagesElement()
    newStage.stage = 20
    newEntry = newStage.newEntriesElement()
    newEntry.flags = 1
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 7
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "11How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "11Another futile attempt at making this thing work"
    newReference = newEntry.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO = True

    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]    

    newEntry = newStage.newEntriesElement()
    newEntry.flags = 1
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 7
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "21How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "21Another futile attempt at making this thing work"
    newReference = newEntry.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO = True

    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newEntry = newStage.newEntriesElement()
    newEntry.flags = 1
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 7
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "31How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "31Another futile attempt at making this thing work"
    newReference = newEntry.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO = True

    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]  

    newStage.entries = [newStage.entries[2], newStage.entries[0]]    

    newStage = newRecord.newStagesElement()
    newStage.stage = 30
    newEntry = newStage.newEntriesElement()
    newEntry.flags = 1
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 7
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "12How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "12Another futile attempt at making this thing work"
    newReference = newEntry.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO = True

    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]    

    newEntry = newStage.newEntriesElement()
    newEntry.flags = 1
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 7
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "22How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "22Another futile attempt at making this thing work"
    newReference = newEntry.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO = True

    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newEntry = newStage.newEntriesElement()
    newEntry.flags = 1
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 7
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newEntry.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "32How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "32Another futile attempt at making this thing work"
    newReference = newEntry.newReferencesElement()
    newReference.reference = 7
    newReference.isSCRO = True
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 8
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 9
    newReference.isSCRO = False
    
    newReference = newEntry.newReferencesElement()
    newReference.reference = 10
    newReference.isSCRO = True

    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]  

    newStage.entries = [newStage.entries[2], newStage.entries[0]]

    newRecord.stages = [newRecord.stages[2], newRecord.stages[0]]

    newTarget = newRecord.newTargetsElement()
    newTarget.targetId = 7
    newTarget.flags = 1
    newTarget.unused1 = [1,2,3]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 7
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newTarget.conditions = [newTarget.conditions[3], newTarget.conditions[1], newTarget.conditions[0]]

    newTarget = newRecord.newTargetsElement()
    newTarget.targetId = 8
    newTarget.flags = 2
    newTarget.unused1 = [1,2,3]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 7
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newTarget.conditions = [newTarget.conditions[3], newTarget.conditions[1], newTarget.conditions[0]]

    newTarget = newRecord.newTargetsElement()
    newTarget.targetId = 9
    newTarget.flags = 3
    newTarget.unused1 = [1,2,3]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 7
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 7
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newTarget.newConditionsElement()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newTarget.conditions = [newTarget.conditions[3], newTarget.conditions[1], newTarget.conditions[0]]

    newRecord.targets = [newRecord.targets[2], newRecord.targets[0]]
    
    print "QUST:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "script     : %08X" % newRecord.script
    print "full       :", newRecord.full
    print "iconPath   :", newRecord.iconPath
    print "flags      :", newRecord.flags
    print "priority   :", newRecord.priority
    
    print "conditions"
    for condition in newRecord.conditions:
        print "  operType  :", condition.operType
        print "  unused1   :", condition.unused1
        print "  compValue :", condition.compValue
        print "  ifunc     :", condition.ifunc
        print "  param1    :", condition.param1
        print "  param2    :", condition.param2
        print "  unused2   :", condition.unused2
        print
    print "stages"
    for stage in newRecord.stages:
        print "  stage :", stage.stage
        print "  entries"
        for entry in stage.entries:
            print "    flags        :", entry.flags
            print "    conditions"
            for condition in entry.conditions:
                print "      operType  :", condition.operType
                print "      unused1   :", condition.unused1
                print "      compValue :", condition.compValue
                print "      ifunc     :", condition.ifunc
                print "      param1    :", condition.param1
                print "      param2    :", condition.param2
                print "      unused2   :", condition.unused2
                print
            print "    text         :", entry.text
            print "    unused1      :", entry.unused1
            print "    numRefs      :", entry.numRefs
            print "    compiledSize :", entry.compiledSize
            print "    lastIndex    :", entry.lastIndex
            print "    scriptType   :", entry.scriptType
            print "    compiled_p   :", entry.compiled_p
            print "    scriptText   :", entry.scriptText
            print "    references"
            for reference in entry.references:
                if(reference.isSCRO):
                    print "      SCRO: %08X" % reference.reference
                else:
                    print "      SCRV:", reference.reference
            print
        print
    print "targets"
    for target in newRecord.targets:
        print "  targetId : %08X" % target.targetId
        print "  flags    :", target.flags
        print "  unused1  :", target.unused1
        print "  conditions"
        for condition in target.conditions:
            print "    operType  :", condition.operType
            print "    unused1   :", condition.unused1
            print "    compValue :", condition.compValue
            print "    ifunc     :", condition.ifunc
            print "    param1    :", condition.param1
            print "    param2    :", condition.param2
            print "    unused2   :", condition.unused2
            print

    print "QUST:CopyAsOverride Test"
    for record in Current[0].QUST:
        record.CopyAsOverride(newMod)

    print "QUST:CopyAsNew Test"
    for record in Current[0].QUST:
        record.CopyAsNew(newMod)

    print "QUST:Save Test - TestQUST.esp"
    newMod.safeSave()
    print "QUST:Finished testing"


def TestIDLE():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestIDLE.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.IDLE:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p
        
        print "conditions"
        for condition in record.conditions:
            print "  operType  :", condition.operType
            print "  unused1   :", condition.unused1
            print "  compValue :", condition.compValue
            print "  ifunc     :", condition.ifunc
            print "  param1    :", condition.param1
            print "  param2    :", condition.param2
            print "  unused2   :", condition.unused2
            print

        print "group  :", record.group
        print "parent : %08X" % record.parent
        print "prevId : %08X" % record.prevId
        
        break

    print "IDLE:Create Record Test"
    newRecord = newMod.createIDLERecord()
    print "IDLE:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "IDLEWarTest"

    print "modPath..."
    newRecord.modPath = r"IDLE\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.06
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 4
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 5
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 6
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newRecord.conditions = [newRecord.conditions[3], newRecord.conditions[1], newRecord.conditions[0]]

    newRecord.group = 1
    newRecord.parent = 7
    newRecord.prevId = 15

    print "IDLE:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p
    
    print "conditions"
    for condition in newRecord.conditions:
        print "  operType  :", condition.operType
        print "  unused1   :", condition.unused1
        print "  compValue :", condition.compValue
        print "  ifunc     :", condition.ifunc
        print "  param1    :", condition.param1
        print "  param2    :", condition.param2
        print "  unused2   :", condition.unused2
        print

    print "group  :", newRecord.group
    print "parent : %08X" % newRecord.parent
    print "prevId : %08X" % newRecord.prevId
    
    print "IDLE:CopyAsOverride Test"
    for record in Current[0].IDLE:
        record.CopyAsOverride(newMod)

    print "IDLE:CopyAsNew Test"
    for record in Current[0].IDLE:
        record.CopyAsNew(newMod)

    print "IDLE:Save Test - TestIDLE.esp"
    newMod.safeSave()
    print "IDLE:Finished testing"


def TestPACK():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestPACK.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.PACK:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "flags   :", record.flags
        print "aiType  :", record.aiType
        print "unused1 :", record.unused1
        
        print "locType   :", record.locType
        if(record.locType != 5):
            print "locId     : %08X" % record.locId
        else:
            print "locId     :", record.locId
        print "locRadius :", record.locRadius
        
        print "month    :", record.month
        print "day      :", record.day
        print "date     :", record.date
        print "time     :", record.time
        print "duration :", record.duration
        
        print "targetType  :", record.targetType
        if(record.targetType != 2):
            print "targetId    : %08X" % record.targetId
        else:
            print "targetId    :", record.targetId
        print "targetCount :", record.targetCount

        print "conditions"
        for condition in record.conditions:
            print "  operType  :", condition.operType
            print "  unused1   :", condition.unused1
            print "  compValue :", condition.compValue
            print "  ifunc     :", condition.ifunc
            print "  param1    :", condition.param1
            print "  param2    :", condition.param2
            print "  unused2   :", condition.unused2
            print
        
        break

    print "PACK:Create Record Test"
    newRecord = newMod.createPACKRecord()
    print "PACK:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "PACKWarTest"

    newRecord.flags = 1
    newRecord.aiType = 2
    newRecord.unused1 = [1,2,3]
    newRecord.locType = 5
    newRecord.locId = 4
    newRecord.locRadius = 5
    newRecord.month = 6
    newRecord.day = 7
    newRecord.date = 8
    newRecord.time = 9
    newRecord.duration = 10
    newRecord.targetType = 1
    newRecord.targetId = 12
    newRecord.targetCount = 13

    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = 4
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = 5
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = 6
    newCondition.param2 = 10
    newCondition.unused2 = [1,2,3,4]
    
    newCondition = newRecord.newConditionsElement()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newRecord.conditions = [newRecord.conditions[3], newRecord.conditions[1], newRecord.conditions[0]]

    print "PACK:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "flags   :", newRecord.flags
    print "aiType  :", newRecord.aiType
    print "unused1 :", newRecord.unused1
    
    print "locType   :", newRecord.locType
    if(newRecord.locType != 5):
        print "locId     : %08X" % newRecord.locId
    else:
        print "locId     :", newRecord.locId
    print "locRadius :", newRecord.locRadius
    
    print "month    :", newRecord.month
    print "day      :", newRecord.day
    print "date     :", newRecord.date
    print "time     :", newRecord.time
    print "duration :", newRecord.duration
    
    print "targetType  :", newRecord.targetType
    if(newRecord.targetType != 2):
        print "targetId    : %08X" % newRecord.targetId
    else:
        print "targetId    :", newRecord.targetId
    print "targetCount :", newRecord.targetCount

    print "conditions"
    for condition in newRecord.conditions:
        print "  operType  :", condition.operType
        print "  unused1   :", condition.unused1
        print "  compValue :", condition.compValue
        print "  ifunc     :", condition.ifunc
        print "  param1    :", condition.param1
        print "  param2    :", condition.param2
        print "  unused2   :", condition.unused2
        print
    
    print "PACK:CopyAsOverride Test"
    for record in Current[0].PACK:
        record.CopyAsOverride(newMod)

    print "PACK:CopyAsNew Test"
    for record in Current[0].PACK:
        record.CopyAsNew(newMod)

    print "PACK:Save Test - TestPACK.esp"
    newMod.safeSave()
    print "PACK:Finished testing"


def TestCSTY():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCSTY.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.CSTY:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "dodgeChance  :", record.dodgeChance
        print "lrChance     :", record.lrChance
        print "unused1      :", record.unused1
        print "lrTimerMin   :", record.lrTimerMin
        print "lrTimerMax   :", record.lrTimerMax
        print "forTimerMin  :", record.forTimerMin
        print "forTimerMax  :", record.forTimerMax
        print "backTimerMin :", record.backTimerMin
        print "backTimerMax :", record.backTimerMax
        print "idleTimerMin :", record.idleTimerMin
        print "idleTimerMax :", record.idleTimerMax
        print "blkChance    :", record.blkChance
        print "atkChance    :", record.atkChance
        print "unused2      :", record.unused2
        print "atkBRecoil   :", record.atkBRecoil
        print "atkBUnc      :", record.atkBUnc
        print "atkBh2h      :", record.atkBh2h
        print "pAtkChance   :", record.pAtkChance
        print "unused3      :", record.unused3
        print "pAtkBRecoil  :", record.pAtkBRecoil
        print "pAtkBUnc     :", record.pAtkBUnc
        print "pAtkNormal   :", record.pAtkNormal
        print "pAtkFor      :", record.pAtkFor
        print "pAtkBack     :", record.pAtkBack
        print "pAtkL        :", record.pAtkL
        print "pAtkR        :", record.pAtkR
        print "unused4      :", record.unused4                    
        print "holdTimerMin :", record.holdTimerMin
        print "holdTimerMax :", record.holdTimerMax
        print "flagsA       :", record.flagsA
        print "acroDodge    :", record.acroDodge
        print "unused5      :", record.unused5
        print "rMultOpt     :", record.rMultOpt
        print "rMultMax     :", record.rMultMax
        print "mDistance    :", record.mDistance
        print "rDistance    :", record.rDistance
        print "buffStand    :", record.buffStand
        print "rStand       :", record.rStand
        print "groupStand   :", record.groupStand
        print "rushChance   :", record.rushChance
        print "unused6      :", record.unused6
        print "rushMult     :", record.rushMult
        print "flagsB       :", record.flagsB
        print "dodgeFMult     :", record.dodgeFMult
        print "dodgeFBase     :", record.dodgeFBase
        print "encSBase       :", record.encSBase
        print "encSMult       :", record.encSMult
        print "dodgeAtkMult   :", record.dodgeAtkMult
        print "dodgeNAtkMult  :", record.dodgeNAtkMult
        print "dodgeBAtkMult  :", record.dodgeBAtkMult
        print "dodgeBNAtkMult :", record.dodgeBNAtkMult
        print "dodgeFAtkMult  :", record.dodgeFAtkMult
        print "dodgeFNAtkMult :", record.dodgeFNAtkMult
        print "blockMult      :", record.blockMult
        print "blockBase      :", record.blockBase
        print "blockAtkMult   :", record.blockAtkMult
        print "blockNAtkMult  :", record.blockNAtkMult
        print "atkMult        :", record.atkMult
        print "atkBase        :", record.atkBase
        print "atkAtkMult     :", record.atkAtkMult
        print "atkNAtkMult    :", record.atkNAtkMult
        print "atkBlockMult   :", record.atkBlockMult
        print "pAtkFBase      :", record.pAtkFBase
        print "pAtkFMult      :", record.pAtkFMult
        break

    print "CSTY:Create Record Test"
    newRecord = newMod.createCSTYRecord()
    print "CSTY:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CSTYWarTest"

    newRecord.dodgeChance = 1
    newRecord.lrChance = 2
    newRecord.unused1 = [1,2]
    newRecord.lrTimerMin = 3
    newRecord.lrTimerMax = 4
    newRecord.forTimerMin = 5
    newRecord.forTimerMax = 6
    newRecord.backTimerMin = 7
    newRecord.backTimerMax = 8
    newRecord.idleTimerMin = 9
    newRecord.idleTimerMax = 10
    newRecord.blkChance = 11
    newRecord.atkChance = 12
    newRecord.unused2 = [3,4]
    newRecord.atkBRecoil = 13
    newRecord.atkBUnc = 14
    newRecord.atkBh2h = 15
    newRecord.pAtkChance = 16
    newRecord.unused3 = [5,6,7]
    newRecord.pAtkBRecoil = 17
    newRecord.pAtkBUnc = 18
    newRecord.pAtkNormal = 19
    newRecord.pAtkFor = 20
    newRecord.pAtkBack = 21
    newRecord.pAtkL = 22
    newRecord.pAtkR = 23
    newRecord.unused4 = [8,9,10]
    newRecord.holdTimerMin = 24
    newRecord.holdTimerMax = 25
    newRecord.flagsA = 1
    newRecord.acroDodge = 26
    newRecord.unused5 = [11,12]
    newRecord.rMultOpt = 27
    newRecord.rMultMax = 28
    newRecord.mDistance = 29
    newRecord.rDistance = 30
    newRecord.buffStand = 31
    newRecord.rStand = 32
    newRecord.groupStand = 33
    newRecord.rushChance = 34
    newRecord.unused6 = [13,14,15]
    newRecord.rushMult = 35
    newRecord.flagsB = 2
    newRecord.dodgeFMult = 36
    newRecord.dodgeFBase = 37
    newRecord.encSBase = 38
    newRecord.encSMult = 39
    newRecord.dodgeAtkMult = 40
    newRecord.dodgeNAtkMult = 41
    newRecord.dodgeBAtkMult = 42
    newRecord.dodgeBNAtkMult = 43
    newRecord.dodgeFAtkMult = 44
    newRecord.dodgeFNAtkMult = 45
    newRecord.blockMult = 46
    newRecord.blockBase = 47
    newRecord.blockAtkMult = 48
    newRecord.blockNAtkMult = 49
    newRecord.atkMult = 50
    newRecord.atkBase = 51
    newRecord.atkAtkMult = 52
    newRecord.atkNAtkMult = 53
    newRecord.atkBlockMult = 54
    newRecord.pAtkFBase = 55
    newRecord.pAtkFMult = 56

    print "CSTY:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "dodgeChance  :", newRecord.dodgeChance
    print "lrChance     :", newRecord.lrChance
    print "unused1      :", newRecord.unused1
    print "lrTimerMin   :", newRecord.lrTimerMin
    print "lrTimerMax   :", newRecord.lrTimerMax
    print "forTimerMin  :", newRecord.forTimerMin
    print "forTimerMax  :", newRecord.forTimerMax
    print "backTimerMin :", newRecord.backTimerMin
    print "backTimerMax :", newRecord.backTimerMax
    print "idleTimerMin :", newRecord.idleTimerMin
    print "idleTimerMax :", newRecord.idleTimerMax
    print "blkChance    :", newRecord.blkChance
    print "atkChance    :", newRecord.atkChance
    print "unused2      :", newRecord.unused2
    print "atkBRecoil   :", newRecord.atkBRecoil
    print "atkBUnc      :", newRecord.atkBUnc
    print "atkBh2h      :", newRecord.atkBh2h
    print "pAtkChance   :", newRecord.pAtkChance
    print "unused3      :", newRecord.unused3
    print "pAtkBRecoil  :", newRecord.pAtkBRecoil
    print "pAtkBUnc     :", newRecord.pAtkBUnc
    print "pAtkNormal   :", newRecord.pAtkNormal
    print "pAtkFor      :", newRecord.pAtkFor
    print "pAtkBack     :", newRecord.pAtkBack
    print "pAtkL        :", newRecord.pAtkL
    print "pAtkR        :", newRecord.pAtkR
    print "unused4      :", newRecord.unused4                    
    print "holdTimerMin :", newRecord.holdTimerMin
    print "holdTimerMax :", newRecord.holdTimerMax
    print "flagsA       :", newRecord.flagsA
    print "acroDodge    :", newRecord.acroDodge
    print "unused5      :", newRecord.unused5
    print "rMultOpt     :", newRecord.rMultOpt
    print "rMultMax     :", newRecord.rMultMax
    print "mDistance    :", newRecord.mDistance
    print "rDistance    :", newRecord.rDistance
    print "buffStand    :", newRecord.buffStand
    print "rStand       :", newRecord.rStand
    print "groupStand   :", newRecord.groupStand
    print "rushChance   :", newRecord.rushChance
    print "unused6      :", newRecord.unused6
    print "rushMult     :", newRecord.rushMult
    print "flagsB       :", newRecord.flagsB
    print "dodgeFMult     :", newRecord.dodgeFMult
    print "dodgeFBase     :", newRecord.dodgeFBase
    print "encSBase       :", newRecord.encSBase
    print "encSMult       :", newRecord.encSMult
    print "dodgeAtkMult   :", newRecord.dodgeAtkMult
    print "dodgeNAtkMult  :", newRecord.dodgeNAtkMult
    print "dodgeBAtkMult  :", newRecord.dodgeBAtkMult
    print "dodgeBNAtkMult :", newRecord.dodgeBNAtkMult
    print "dodgeFAtkMult  :", newRecord.dodgeFAtkMult
    print "dodgeFNAtkMult :", newRecord.dodgeFNAtkMult
    print "blockMult      :", newRecord.blockMult
    print "blockBase      :", newRecord.blockBase
    print "blockAtkMult   :", newRecord.blockAtkMult
    print "blockNAtkMult  :", newRecord.blockNAtkMult
    print "atkMult        :", newRecord.atkMult
    print "atkBase        :", newRecord.atkBase
    print "atkAtkMult     :", newRecord.atkAtkMult
    print "atkNAtkMult    :", newRecord.atkNAtkMult
    print "atkBlockMult   :", newRecord.atkBlockMult
    print "pAtkFBase      :", newRecord.pAtkFBase
    print "pAtkFMult      :", newRecord.pAtkFMult
    
    print "CSTY:CopyAsOverride Test"
    for record in Current[0].CSTY:
        record.CopyAsOverride(newMod)

    print "CSTY:CopyAsNew Test"
    for record in Current[0].CSTY:
        record.CopyAsNew(newMod)

    print "CSTY:Save Test - TestCSTY.esp"
    newMod.safeSave()
    print "CSTY:Finished testing"


def TestLSCR():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLSCR.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.LSCR:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "iconPath :", record.iconPath
        print "text     :", record.text
        print "locations"
        for location in record.locations:
            print "  direct   : %08X" % location.direct
            print "  indirect : %08X" % location.indirect
            print "  gridY    :", location.gridY
            print "  gridX    :", location.gridX

        break

    print "LSCR:Create Record Test"
    newRecord = newMod.createLSCRRecord()
    print "LSCR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "LSCRWarTest"

    newRecord.iconPath = r"LSCR\War\Test\Longer\Than\Usual\Just\Because\Test.dds"
    newRecord.text = "Hrm, what on earth could be going on?\n I don't know what this is all about, but I'm sure it'll be fine"

    newLocation = newRecord.newLocationsElement()
    newLocation.direct = 7
    newLocation.indirect = 10
    newLocation.gridY = 0
    newLocation.gridX = 1
    
    newLocation = newRecord.newLocationsElement()
    newLocation.direct = 8
    newLocation.indirect = 11
    newLocation.gridY = 2
    newLocation.gridX = 3
    
    newLocation = newRecord.newLocationsElement()
    newLocation.direct = 9
    newLocation.indirect = 12
    newLocation.gridY = 4
    newLocation.gridX = 5
    
    newLocation = newRecord.newLocationsElement()
    newLocation.direct = 10
    newLocation.indirect = 13
    newLocation.gridY = 6
    newLocation.gridX = 7

    newRecord.locations = [newRecord.locations[3], newRecord.locations[0], newRecord.locations[2]]
    
    print "LSCR:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "iconPath :", newRecord.iconPath
    print "text     :", newRecord.text
    print "locations"
    for location in newRecord.locations:
        print "  direct   : %08X" % location.direct
        print "  indirect : %08X" % location.indirect
        print "  gridY    :", location.gridY
        print "  gridX    :", location.gridX
        
    print "LSCR:CopyAsOverride Test"
    for record in Current[0].LSCR:
        record.CopyAsOverride(newMod)

    print "LSCR:CopyAsNew Test"
    for record in Current[0].LSCR:
        record.CopyAsNew(newMod)

    print "LSCR:Save Test - TestLSCR.esp"
    newMod.safeSave()
    print "LSCR:Finished testing"


def TestLVSP():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLVSP.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.LVSP:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "chanceNone :", record.chanceNone
        print "flags      :", record.flags
        print "entries"
        for entry in record.entries:
            print
            print "  level   :", entry.level
            print "  unused1 :", entry.unused1
            print "  listId  : %08X" % entry.listId
            print "  count   :", entry.count
            print "  unused2 :", entry.unused2
        break

    print "LVSP:Create Record Test"
    newRecord = newMod.createLVSPRecord()
    print "LVSP:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "LVSPWarTest"

    newRecord.chanceNone = 20
    newRecord.flags = 1

    entry = newRecord.newEntriesElement()
    entry.level = 1
    entry.unused1 = [0x14, 0xFF]
    entry.listId = 0x0100000A
    entry.count = 2
    entry.unused2 = [0x15, 0xFF]
    entry = newRecord.newEntriesElement()
    entry.level = 3
    entry.unused1 = [0x16, 0xFF]
    entry.listId = 0x0000000B
    entry.count = 4
    entry.unused2 = [0x17, 0xFF]
    entry = newRecord.newEntriesElement()
    entry.level = 5
    entry.unused1 = [0x18, 0xFF]
    entry.listId = 0x0000000C
    entry.count = 6
    entry.unused2 = [0x19, 0xFF]
    entry = newRecord.newEntriesElement()
    entry.level = 7
    entry.unused1 = [0x20, 0xFF]
    entry.listId = 0x0000000D
    entry.count = 8
    entry.unused2 = [0x21, 0xFF]
    newRecord.entries = [newRecord.entries[3], newRecord.entries[2], newRecord.entries[0]]

    print "LVSP:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "chanceNone :", newRecord.chanceNone
    print "flags      :", newRecord.flags
    print "entries"
    for entry in newRecord.entries:
        print
        print "  level   :", entry.level
        print "  unused1 :", entry.unused1
        print "  listId  : %08X" % entry.listId
        print "  count   :", entry.count
        print "  unused2 :", entry.unused2

    print "LVSP:CopyAsOverride Test"
    for record in Current[0].LVSP:
        record.CopyAsOverride(newMod)

    print "LVSP:CopyAsNew Test"
    for record in Current[0].LVSP:
        record.CopyAsNew(newMod)

    print "LVSP:Save Test - TestLVSP.esp"
    newMod.safeSave()
    print "LVSP:Finished testing"


def TestANIO():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestANIO.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.ANIO:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "modPath :", record.modPath
        print "modb    :", record.modb
        print "modt_p  :", record.modt_p

        print "animationId : %08X" % record.animationId       

        break

    print "ANIO:Create Record Test"
    newRecord = newMod.createANIORecord()
    print "ANIO:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "ANIOWarTest"

    print "modPath..."
    newRecord.modPath = r"ANIO\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.76
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newRecord.animationId = 7
    print "ANIO:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "animationId : %08X" % newRecord.animationId     
    
    print "ANIO:CopyAsOverride Test"
    for record in Current[0].ANIO:
        record.CopyAsOverride(newMod)

    print "ANIO:CopyAsNew Test"
    for record in Current[0].ANIO:
        record.CopyAsNew(newMod)

    print "ANIO:Save Test - TestANIO.esp"
    newMod.safeSave()
    print "ANIO:Finished testing"


def TestWATR():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestWATR.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.WATR:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "texture       :", record.texture
        print "opacity       :", record.opacity
        print "flags         :", record.flags                    
        print "material      :", record.material                    
        print "sound         : %08X" % record.sound                    
        print "windVelocity  :", record.windVelocity
        print "windDirection :", record.windDirection
        print "waveAmp       :", record.waveAmp
        print "waveFreq      :", record.waveFreq
        print "sunPower      :", record.sunPower
        print "reflectAmt    :", record.reflectAmt
        print "fresnelAmt    :", record.fresnelAmt
        print "xSpeed        :", record.xSpeed
        print "ySpeed        :", record.ySpeed
        print "fogNear       :", record.fogNear
        print "fogFar        :", record.fogFar
        print "shallowRed    :", record.shallowRed
        print "shallowGreen  :", record.shallowGreen
        print "shallowBlue   :", record.shallowBlue
        print "unused1       :", record.unused1
        print "deepRed       :", record.deepRed
        print "deepGreen     :", record.deepGreen
        print "deepBlue      :", record.deepBlue
        print "unused2       :", record.unused2
        print "reflRed       :", record.reflRed
        print "reflGreen     :", record.reflGreen
        print "reflBlue      :", record.reflBlue                    
        print "unused3       :", record.unused3
        print "blend         :", record.blend
        print "unused4       :", record.unused4
        print "rainForce     :", record.rainForce
        print "rainVelocity  :", record.rainVelocity
        print "rainFalloff   :", record.rainFalloff
        print "rainDampner   :", record.rainDampner
        print "rainSize      :", record.rainSize
        print "dispForce     :", record.dispForce
        print "dispVelocity  :", record.dispVelocity
        print "dispFalloff   :", record.dispFalloff
        print "dispDampner   :", record.dispDampner
        print "dispSize      :", record.dispSize
        print "damage        :", record.damage                    
        print "dayWater      : %08X" % record.dayWater
        print "nightWater    : %08X" % record.nightWater
        print "underWater    : %08X" % record.underWater    
        break

    print "WATR:Create Record Test"
    newRecord = newMod.createWATRRecord()
    print "WATR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WATRWarTest"

    newRecord.texture = r"WATR\Texture\Path\Test\1.dds"
    newRecord.opacity = 1
    newRecord.flags = 2             
    newRecord.material = r"WATR\Material\Path\Test\2.dds"                
    newRecord.sound = 7                    
    newRecord.windVelocity = 3
    newRecord.windDirection = 4
    newRecord.waveAmp = 5
    newRecord.waveFreq = 6
    newRecord.sunPower = 7
    newRecord.reflectAmt = 8
    newRecord.fresnelAmt = 9
    newRecord.xSpeed = 10
    newRecord.ySpeed = 11
    newRecord.fogNear = 12
    newRecord.fogFar = 13
    newRecord.shallowRed = 14
    newRecord.shallowGreen = 15
    newRecord.shallowBlue = 16
    newRecord.unused1 = [1]
    newRecord.deepRed = 17
    newRecord.deepGreen = 18
    newRecord.deepBlue = 19
    newRecord.unused2 = [2]
    newRecord.reflRed = 20
    newRecord.reflGreen = 21
    newRecord.reflBlue = 22
    newRecord.unused3 = [3]
    newRecord.blend = 23
    newRecord.unused4 = [4,5,6]
    newRecord.rainForce = 24
    newRecord.rainVelocity = 25
    newRecord.rainFalloff = 26
    newRecord.rainDampner = 27
    newRecord.rainSize = 28
    newRecord.dispForce = 29
    newRecord.dispVelocity = 30
    newRecord.dispFalloff = 31
    newRecord.dispDampner = 32
    newRecord.dispSize = 33
    newRecord.damage = 34                   
    newRecord.dayWater = 10
    newRecord.nightWater = 14
    newRecord.underWater = 35    

    print "WATR:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "texture       :", newRecord.texture
    print "opacity       :", newRecord.opacity
    print "flags         :", newRecord.flags                    
    print "material      :", newRecord.material                    
    print "sound         : %08X" % newRecord.sound                    
    print "windVelocity  :", newRecord.windVelocity
    print "windDirection :", newRecord.windDirection
    print "waveAmp       :", newRecord.waveAmp
    print "waveFreq      :", newRecord.waveFreq
    print "sunPower      :", newRecord.sunPower
    print "reflectAmt    :", newRecord.reflectAmt
    print "fresnelAmt    :", newRecord.fresnelAmt
    print "xSpeed        :", newRecord.xSpeed
    print "ySpeed        :", newRecord.ySpeed
    print "fogNear       :", newRecord.fogNear
    print "fogFar        :", newRecord.fogFar
    print "shallowRed    :", newRecord.shallowRed
    print "shallowGreen  :", newRecord.shallowGreen
    print "shallowBlue   :", newRecord.shallowBlue
    print "unused1       :", newRecord.unused1
    print "deepRed       :", newRecord.deepRed
    print "deepGreen     :", newRecord.deepGreen
    print "deepBlue      :", newRecord.deepBlue
    print "unused2       :", newRecord.unused2
    print "reflRed       :", newRecord.reflRed
    print "reflGreen     :", newRecord.reflGreen
    print "reflBlue      :", newRecord.reflBlue                    
    print "unused3       :", newRecord.unused3
    print "blend         :", newRecord.blend
    print "unused4       :", newRecord.unused4
    print "rainForce     :", newRecord.rainForce
    print "rainVelocity  :", newRecord.rainVelocity
    print "rainFalloff   :", newRecord.rainFalloff
    print "rainDampner   :", newRecord.rainDampner
    print "rainSize      :", newRecord.rainSize
    print "dispForce     :", newRecord.dispForce
    print "dispVelocity  :", newRecord.dispVelocity
    print "dispFalloff   :", newRecord.dispFalloff
    print "dispDampner   :", newRecord.dispDampner
    print "dispSize      :", newRecord.dispSize
    print "damage        :", newRecord.damage                    
    print "dayWater      : %08X" % newRecord.dayWater
    print "nightWater    : %08X" % newRecord.nightWater
    print "underWater    : %08X" % newRecord.underWater    
    
    print "WATR:CopyAsOverride Test"
    for record in Current[0].WATR:
        record.CopyAsOverride(newMod)

    print "WATR:CopyAsNew Test"
    for record in Current[0].WATR:
        record.CopyAsNew(newMod)

    print "WATR:Save Test - TestWATR.esp"
    newMod.safeSave()
    print "WATR:Finished testing"


def TestEFSH():
    Current = Collection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestEFSH.esp", True)
    Current.minimalLoad(LoadMasters=True)

    for record in Current.EFSH:
        print
        print "fid     : %08X" % record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "fillTexture     :", record.fillTexture
        print "particleTexture :", record.particleTexture
        print "flags           :", record.flags
        print "unused1         :", record.unused1
        print "memSBlend       :", record.memSBlend
        print "memBlendOp      :", record.memBlendOp
        print "memZFunc        :", record.memZFunc
        print "fillRed         :", record.fillRed
        print "fillGreen       :", record.fillGreen
        print "fillBlue        :", record.fillBlue
        print "unused2         :", record.unused2
        print "fillAIn         :", record.fillAIn
        print "fillAFull       :", record.fillAFull
        print "fillAOut        :", record.fillAOut
        print "fillAPRatio     :", record.fillAPRatio
        print "fillAAmp        :", record.fillAAmp
        print "fillAFreq       :", record.fillAFreq
        print "fillAnimSpdU    :", record.fillAnimSpdU
        print "fillAnimSpdV    :", record.fillAnimSpdV
        print "edgeOff         :", record.edgeOff
        print "edgeRed         :", record.edgeRed
        print "edgeGreen       :", record.edgeGreen
        print "edgeBlue        :", record.edgeBlue
        print "unused3         :", record.unused3
        print "edgeAIn         :", record.edgeAIn
        print "edgeAFull       :", record.edgeAFull
        print "edgeAOut        :", record.edgeAOut
        print "edgeAPRatio     :", record.edgeAPRatio
        print "edgeAAmp        :", record.edgeAAmp
        print "edgeAFreq       :", record.edgeAFreq
        print "fillAFRatio     :", record.fillAFRatio
        print "edgeAFRatio     :", record.edgeAFRatio
        print "memDBlend       :", record.memDBlend
        print "partSBlend      :", record.partSBlend
        print "partBlendOp     :", record.partBlendOp
        print "partZFunc       :", record.partZFunc
        print "partDBlend      :", record.partDBlend
        print "partBUp         :", record.partBUp
        print "partBFull       :", record.partBFull
        print "partBDown       :", record.partBDown
        print "partBFRatio     :", record.partBFRatio
        print "partBPRatio     :", record.partBPRatio
        print "partLTime       :", record.partLTime
        print "partLDelta      :", record.partLDelta
        print "partNSpd        :", record.partNSpd
        print "partNAcc        :", record.partNAcc
        print "partVel1        :", record.partVel1
        print "partVel2        :", record.partVel2
        print "partVel3        :", record.partVel3
        print "partAcc1        :", record.partAcc1
        print "partAcc2        :", record.partAcc2
        print "partAcc3        :", record.partAcc3
        print "partKey1        :", record.partKey1
        print "partKey2        :", record.partKey2
        print "partKey1Time    :", record.partKey1Time
        print "partKey2Time    :", record.partKey2Time
        print "key1Red         :", record.key1Red
        print "key1Green       :", record.key1Green
        print "key1Blue        :", record.key1Blue
        print "unused4         :", record.unused4
        print "key2Red         :", record.key2Red
        print "key2Green       :", record.key2Green
        print "key2Blue        :", record.key2Blue
        print "unused5         :", record.unused5
        print "key3Red         :", record.key3Red
        print "key3Green       :", record.key3Green
        print "key3Blue        :", record.key3Blue
        print "unused6         :", record.unused6
        print "key1A           :", record.key1A
        print "key2A           :", record.key2A
        print "key3A           :", record.key3A
        print "key1Time        :", record.key1Time
        print "key2Time        :", record.key2Time
        print "key3Time        :", record.key3Time

        break

    print "EFSH:Create Record Test"
    newRecord = newMod.createEFSHRecord()
    print "EFSH:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "EFSHWarTest"

    newRecord.fillTexture = r"EFSH\fillTexture\Path\Test\1.dds"
    newRecord.particleTexture = r"EFSH\particleTexture\Path\Test\2.dds"
    newRecord.flags = 1
    newRecord.unused1 = [1,2,3]
    newRecord.memSBlend = 2
    newRecord.memBlendOp = 3
    newRecord.memZFunc = 4
    newRecord.fillRed = 5
    newRecord.fillGreen = 6
    newRecord.fillBlue = 7
    newRecord.unused2 = [4]
    newRecord.fillAIn = 8
    newRecord.fillAFull = 9
    newRecord.fillAOut = 10
    newRecord.fillAPRatio = 11
    newRecord.fillAAmp = 12
    newRecord.fillAFreq = 13
    newRecord.fillAnimSpdU = 14
    newRecord.fillAnimSpdV = 15
    newRecord.edgeOff = 16
    newRecord.edgeRed = 17
    newRecord.edgeGreen = 18
    newRecord.edgeBlue = 19
    newRecord.unused3 = [5]
    newRecord.edgeAIn = 20
    newRecord.edgeAFull = 21
    newRecord.edgeAOut = 22
    newRecord.edgeAPRatio = 23
    newRecord.edgeAAmp = 24
    newRecord.edgeAFreq = 25
    newRecord.fillAFRatio = 26
    newRecord.edgeAFRatio = 27
    newRecord.memDBlend = 28
    newRecord.partSBlend = 29
    newRecord.partBlendOp = 30
    newRecord.partZFunc = 31
    newRecord.partDBlend = 32
    newRecord.partBUp = 33
    newRecord.partBFull = 34
    newRecord.partBDown = 35
    newRecord.partBFRatio = 36
    newRecord.partBPRatio = 37
    newRecord.partLTime = 38
    newRecord.partLDelta = 39
    newRecord.partNSpd = 40
    newRecord.partNAcc = 41
    newRecord.partVel1 = 42
    newRecord.partVel2 = 43
    newRecord.partVel3 = 44
    newRecord.partAcc1 = 45
    newRecord.partAcc2 = 46
    newRecord.partAcc3 = 47
    newRecord.partKey1 = 48
    newRecord.partKey2 = 49
    newRecord.partKey1Time = 50
    newRecord.partKey2Time = 51
    newRecord.key1Red = 52
    newRecord.key1Green = 53
    newRecord.key1Blue = 54
    newRecord.unused4 = [6]
    newRecord.key2Red = 55
    newRecord.key2Green = 56
    newRecord.key2Blue = 57
    newRecord.unused5 = [7]
    newRecord.key3Red = 58
    newRecord.key3Green = 59
    newRecord.key3Blue = 60
    newRecord.unused6 = [8]
    newRecord.key1A = 61
    newRecord.key2A = 62
    newRecord.key3A = 63
    newRecord.key1Time = 64
    newRecord.key2Time = 65
    newRecord.key3Time = 66

    print "EFSH:Set Test Results"
    print
    print "fid    : %08X" % newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "fillTexture     :", newRecord.fillTexture
    print "particleTexture :", newRecord.particleTexture
    print "flags           :", newRecord.flags
    print "unused1         :", newRecord.unused1
    print "memSBlend       :", newRecord.memSBlend
    print "memBlendOp      :", newRecord.memBlendOp
    print "memZFunc        :", newRecord.memZFunc
    print "fillRed         :", newRecord.fillRed
    print "fillGreen       :", newRecord.fillGreen
    print "fillBlue        :", newRecord.fillBlue
    print "unused2         :", newRecord.unused2
    print "fillAIn         :", newRecord.fillAIn
    print "fillAFull       :", newRecord.fillAFull
    print "fillAOut        :", newRecord.fillAOut
    print "fillAPRatio     :", newRecord.fillAPRatio
    print "fillAAmp        :", newRecord.fillAAmp
    print "fillAFreq       :", newRecord.fillAFreq
    print "fillAnimSpdU    :", newRecord.fillAnimSpdU
    print "fillAnimSpdV    :", newRecord.fillAnimSpdV
    print "edgeOff         :", newRecord.edgeOff
    print "edgeRed         :", newRecord.edgeRed
    print "edgeGreen       :", newRecord.edgeGreen
    print "edgeBlue        :", newRecord.edgeBlue
    print "unused3         :", newRecord.unused3
    print "edgeAIn         :", newRecord.edgeAIn
    print "edgeAFull       :", newRecord.edgeAFull
    print "edgeAOut        :", newRecord.edgeAOut
    print "edgeAPRatio     :", newRecord.edgeAPRatio
    print "edgeAAmp        :", newRecord.edgeAAmp
    print "edgeAFreq       :", newRecord.edgeAFreq
    print "fillAFRatio     :", newRecord.fillAFRatio
    print "edgeAFRatio     :", newRecord.edgeAFRatio
    print "memDBlend       :", newRecord.memDBlend
    print "partSBlend      :", newRecord.partSBlend
    print "partBlendOp     :", newRecord.partBlendOp
    print "partZFunc       :", newRecord.partZFunc
    print "partDBlend      :", newRecord.partDBlend
    print "partBUp         :", newRecord.partBUp
    print "partBFull       :", newRecord.partBFull
    print "partBDown       :", newRecord.partBDown
    print "partBFRatio     :", newRecord.partBFRatio
    print "partBPRatio     :", newRecord.partBPRatio
    print "partLTime       :", newRecord.partLTime
    print "partLDelta      :", newRecord.partLDelta
    print "partNSpd        :", newRecord.partNSpd
    print "partNAcc        :", newRecord.partNAcc
    print "partVel1        :", newRecord.partVel1
    print "partVel2        :", newRecord.partVel2
    print "partVel3        :", newRecord.partVel3
    print "partAcc1        :", newRecord.partAcc1
    print "partAcc2        :", newRecord.partAcc2
    print "partAcc3        :", newRecord.partAcc3
    print "partKey1        :", newRecord.partKey1
    print "partKey2        :", newRecord.partKey2
    print "partKey1Time    :", newRecord.partKey1Time
    print "partKey2Time    :", newRecord.partKey2Time
    print "key1Red         :", newRecord.key1Red
    print "key1Green       :", newRecord.key1Green
    print "key1Blue        :", newRecord.key1Blue
    print "unused4         :", newRecord.unused4
    print "key2Red         :", newRecord.key2Red
    print "key2Green       :", newRecord.key2Green
    print "key2Blue        :", newRecord.key2Blue
    print "unused5         :", newRecord.unused5
    print "key3Red         :", newRecord.key3Red
    print "key3Green       :", newRecord.key3Green
    print "key3Blue        :", newRecord.key3Blue
    print "unused6         :", newRecord.unused6
    print "key1A           :", newRecord.key1A
    print "key2A           :", newRecord.key2A
    print "key3A           :", newRecord.key3A
    print "key1Time        :", newRecord.key1Time
    print "key2Time        :", newRecord.key2Time
    print "key3Time        :", newRecord.key3Time
    
    print "EFSH:CopyAsOverride Test"
    for record in Current[0].EFSH:
        record.CopyAsOverride(newMod)

    print "EFSH:CopyAsNew Test"
    for record in Current[0].EFSH:
        record.CopyAsNew(newMod)

    print "EFSH:Save Test - TestEFSH.esp"
    newMod.safeSave()
    print "EFSH:Finished testing"

from timeit import Timer

##print "1TestMinimalLoad"
##test = [Timer('TestMinimalLoad()', 'from __main__ import TestMinimalLoad').timeit(1) for x in range(0, 1)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##print "10TestMinimalLoad"
##test = [Timer('TestMinimalLoad()', 'from __main__ import TestMinimalLoad').timeit(1) for x in range(0, 10)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)
    
##print "1TestFullLoad"
##test = [Timer('TestFullLoad()', 'from __main__ import TestFullLoad').timeit(1) for x in range(0, 1)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##print "10TestFullLoad"
##test = [Timer('TestFullLoad()', 'from __main__ import TestFullLoad').timeit(1) for x in range(0, 10)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##phonenumber = raw_input(">")

##print "1TestReadWriteAll"
##test = [Timer('TestReadWriteAll()', 'from __main__ import TestReadWriteAll').timeit(1) for x in range(0, 1)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##phonenumber = raw_input(">")
Current = Collection()
Current.addMod("Oblivion.esm")
Current.fullLoad(LoadMasters=True)
##Current.minimalLoad(LoadMasters=True)
phonenumber = raw_input(">")
del Current
phonenumber = raw_input("!")


##TestReadWriteAll()
##TestTES4()
##TestGMST()
##TestGLOB()
##TestCLAS()
##TestFACT()
##TestHAIR()
##TestEYES()
##TestRACE()
##TestSOUN()
##TestSKIL()
##TestMGEF()
##TestSCPT()
##TestLTEX()
##TestENCH()
##TestSPEL()
##TestBSGN()
##TestACTI()
##TestAPPA()
##TestARMO()
##TestBOOK()
##TestCLOT()
##TestCONT()
##TestDOOR()
##TestINGR()
##TestLIGH()
##TestMISC()
##TestSTAT()
##TestGRAS()
##TestTREE()
##TestFLOR()
##TestFURN()
##TestWEAP()
##TestAMMO()
##TestNPC_()
##TestCREA()
##TestLVLC()
##TestSLGM()
##TestKEYM()
##TestALCH()
##TestSBSP()
##TestSGST()
##TestLVLI()
##TestWTHR()
##TestCLMT()
##TestREGN()
##TestCELL()
##TestWRLD()
##TestDIAL()
##TestQUST()
##TestIDLE()
##TestPACK()
##TestCSTY()
##TestLSCR()
##TestLVSP()
##TestANIO()
##TestWATR()
##TestEFSH()
####Current.debug(6, True)
##print "Entirely Finished\n"

##del Current