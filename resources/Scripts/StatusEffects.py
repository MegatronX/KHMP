from EntityModule import *
from ComponentModule import *
from StatusEffectsModule import *
from CharacterModule import *
import copy



class MultiApplyExtension(ApplyEffectComponent):
    def __init__(self, Owner, OtherComponents = None):
        self.OtherComponents = OtherComponents
        print Owner.GetName()
		#if (self.OtherComponents != None):
		#	for comp in self.OtherComponents):
		#		comp.DispatchSignals = False
        ApplyEffectComponent.__init__(self, Owner)
    def Apply(self, Character):
		if (self.OtherComponents != None):
			for comp in self.OtherComponents:
				comp.Apply(Character)
		ApplyEffectComponent.Apply(self, Character)
    def UnApply(self, Character):
		if (self.OtherComponents != None):
			for comp in self.OtherComponents:
				comp.UnApply(Character)
		ApplyEffectComponent.UnApply(self, Character)
    def Clone(self):
        return copy.deepcopy(self)

class SingleStatBoostApply(ApplyEffectComponent):
	def __init__(self, Owner, _Stat, _Multiplier):
		self.Stat = _Stat
		self.Multiplier = _Multiplier
		#self.DispatchSignals = DispatchSignals
		ApplyEffectComponent.__init__(self, Owner)
	def Apply(self, Character):
		SM = Character.GetStatsManager()
                stat = SM.GetBattleStat(self.Stat)
                print "Tester"
		SM.SetBattleStat(self.Stat, int(SM.GetBattleStat(self.Stat) * self.Multiplier))
		#if (self.DispatchSignals):
		ApplyEffectComponent.Apply(self, Character)
	def UnApply(self, Character):
		SM = Character.GetStatsManager()
		SM.SetBattleStat(self.Stat, int(SM.GetBattleStat(self.Stat) / self.Multiplier))
		#if (self.DispatchSignals):
		ApplyEffectComponent.UnApply(self, Character)
	def Clone(self):
		return copy.deepcopy(self)

class MultiStatBoostApply(ApplyEffectComponent):
	def __init__(self, Owner, StatBoosts):
		self.StatBoosts = StatBoosts;
		ApplyEffectComponent.__init__(self, Owner)
	def Apply(self, Character):
		if (self.StatBoosts != None):
			SM = Character.GetStatsManager()
			for stat, boost in self.StatBoosts.iteritems():
				SM.SetBattleStat(int(SM.GetBattleStat(stat) * boost))
		if (self.DispatchSignals):
			ApplyEffectComponent.Apply(self, Character)
	def UnApply(self, Character):
		if (self.StatBoosts != None):
			SM = Character.GetStatsManager()
			for stat, boost in self.StatBoosts.iteritems():
				SM.SetBattleStat(int(SM.GetBattleStat(stat) / boost))
		if (self.DispatchSignals):
			ApplyEffectComponent.UnApply(self, Character)
	def Clone(self):
		return copy.deepcopy(self)


class StatusResistanceBoostApply(ApplyEffectComponent):
	def __init__(self, Owner, StatusBoosts):
		self.StatusBoosts = StatusBoosts
		ApplyEffectComponent.__init__(self, Owner)

	def Apply(self, Character):
		if (self.StatusBoosts != None):
			SEM = Character.GetStatusEffectsManager()
			for status, boost in self.StatusBoosts.iteritems():	
				SEM.SetStatusResistance(status, SEM.GetStatusResistance(status) + boost)
		if (self.DispatchSignals):
			ApplyEffectComponent.Appy(self, Character)
	def UnApply(self, Character):
		if (self.StatusBoosts != None):
			SEM = Character.GetStatusEffectsManager()
			for status, boost in self.StatusBoosts.iteritems():
				SEM.SetStatusResistance(status, SEM.GetStatusResistance(status) - boost)
		if (self.DispatchSignals):	
			ApplyEffectComponent.UnApply(self, Character)

	def Clone(self):
		return copy.deepcopy(self)

CurrentSE = StatusEffect(None, "Haste", True)
Mult = SingleStatBoostApply(CurrentSE, Stat.Speed, 1.5)
CurrentSE.RegisterComponent("ApplyEffectComponent", Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Haste+", True)
Mult = SingleStatBoostApply(CurrentSE, Stat.Speed, 1.75)
CurrentSE.RegisterComponent("ApplyEffectComponent", Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Juggernaut", True)
Mult = SingleStatBoostApply(CurrentSE, Stat.Strength, 1.5);
CurrentSE.RegisterComponent("ApplyEffectComponent", Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Bubble", True)
Mult = SingleStatBoostApply(CurrentSE, Stat.HP, 1.5)
CurrentSE.RegisterComponent("ApplyEffectComponent", Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Slow", False)
Mult = SingleStatBoostApply(CurrentSE, Stat.Speed, 0.5)
CurrentSE.RegisterComponent("ApplyEffectComponent", Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Slow+", False)
Mult = SingleStatBoostApply(CurrentSE, Stat.Speed, 0.3)
CurrentSE.RegisterComponent("ApplyEffectComponent", Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Blind", False)
Mult = SingleStatBoostApply(CurrentSE, Stat.Accuracy, 0.3)
CurrentSE.RegisterComponent("ApplyEffectComponent", Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Fever", False)
Mult = MultiStatBoostApply(CurrentSE, {Stat.Speed: 1.25, Stat.Vitality: 0.65, Stat.Spirit: 0.65})
CurrentSE.RegisterComponent("ApplyEffectComponent", Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Frozen", False)
Mult = MultiStatBoostApply(CurrentSE, {Stat.Speed: 0.6, Stat.Vitality: 1.2, Stat.Spirit: 1.2})
CurrentSE.RegisterComponent("ApplyEffectComponent", Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

#StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)





