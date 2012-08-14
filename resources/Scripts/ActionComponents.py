from ComponentModule import *
from EntityModule import *
from ActionModule import *
from ElementModule import *
from BattleModule import *

import copy

class ConstantDamageComponent(DamageCalculationComponent):
    def __init__(self, Owner, ConstDmg):
        self.ConstDamage = ConstDmg

        DamageCalculationComponent.__init__(self, Owner)
    def CalculateDamage(self, action, target, mechanics):
        return self.ConstDamage

    def Clone(self):
        return copy.deepcopy(self)
