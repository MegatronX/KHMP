from ItemModule import *
from ComponentModule import *
from EntityModule import *
from GameInstanceModule import *
from CharacterModule import *
from ActionModule import *
from BattleModule import *
import xml.etree.cElementTree as xml

import copy
class HealingComponent(UseComponent):
    def __init__(self, FieldHealMap, BattleHealMap = None):
        self.FieldHealMap = FieldHealMap
        self.BattleHealMap = BattleHealMap
        UseComponent.__init__(self, "HealUseModule", True, True)
    def Use(self, action):
        print "PrePrint"
        print action.GetName()
        clone = action.Clone()
        print clone.GetName()
        print "Ughhhh"
        return False
    def BattleUse(self, action, field):
        print "BattleTest"
    def Clone(self):
        print "herp"
        return copy.deepcopy(self)

def ItemFactory(ItemNode):
    ItemName = ItemNode.attrib["name"]
    CurrentItem = Entity(ItemName, EntityTypes.ItemEntity)
    #print ItemName
    componentNode = ItemNode.find("Components")
    if (componentNode != None):
        components = componentNode.getchildren()
        for component in components:
            if component.tag == "HealingComponents":
                healingcomponents = component.getchildren()
                for healingcomponent in healingcomponents:
                    if (healingcomponent.tag == "BattleHealingComponent" or healingcomponent.tag == "FieldHealingComponent"):
                        targetstats = healingcomponent.getchildren()
                        HealMap = {}
                        for targetstat in targetstats:
                            if (targetstat.tag == "HP" or targetstat.tag == "MP" or targetstat.tag == "SP"):
                                amount = targetstat.attrib["amount"]
                                type = targetstat.attrib["type"]
                                HealMap[targetstat.tag] = (amount, type)
                        HealComp = HealingComponent(HealMap, HealMap)
                        CurrentItem.RegisterComponent(healingcomponent.tag, HealComp)

                #HealComp = HealingComponent(None)
                #CurrentItem.RegisterComponent("Healing Component", HealComp)
    return CurrentItem  

itemTree = xml.parse("..\\..\\..\\resources\\XML Databases\\Items.xml")
itemsRoot = itemTree.getroot()
itemList = itemsRoot.findall("Item")
if (itemList != None):
    for item in itemList:
        targitem = ItemFactory(item)
        ItemModule.ItemLibrary.AddItem(targitem)
        #ItemModule.ItemLibrary.AddItem(targitem)



    

    





