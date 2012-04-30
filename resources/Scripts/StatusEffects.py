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
		
class StatRestorePostMove(PostMoveEffect):
	def __init__(self, Owner, StatRest, StatRate):
		self.StatRest = StatRest;
		self.StatRate = StatRate;
		ApplyEffectComponent.__init__(self,Owner)
	
	def PostUse(self, Action, RootAction):
		Damage = Action.GetFinalDamage()
		if (self.StatRest != None and self.StatRate != None):
			Character = self.GetOwner().GetHoldingCharacter()
			if (Character != None):
				SM = Character.GetStatManager()
				if (SM != None):
					if (self.StatRate == Stats.HP):
						SM.SetHP(SM.GetHP() + int(self.StatRate * self.StatRest))
					if (self.StatRate == Stats.MP):
						SM.SetMP(SM.GetMP() + int(self.StatRate * self.StatRest))
					if (self.StatRate == Stats.SP):
						SM.SetSP(SM.GetSP() + int(self.StatRate * self.StatRest))
	def Clone(self):
		return copy.deepcopy(self)
						
class StatTurbo(ActionModifierComponent):
	def __init__(self, Owner, Stat, TurboRate, CostRate, ActiveOnMagic, ActiveOnPhysical):
		self.TargetStat = Stat
		self.TurboRate = TurboRate
		ActionModifierComponent(self, Owner)
		
	def ModifyAction(self, Action, Mechanics):
		if (Action.Users.HasUser(self.Owner.GetHolder())):
			mgW = Action.GetMagicWeight()
			phyW = Action.GetPhysicalWeight()
			Booster = int(CalcBoost(self, Action, mgW, phyW, ActiveOnMagic, ActiveOnPhysical)) 
			StatCost = CalcStatCost(Action, Booster)
			Action.SetPower(Action.GetPower() + Booster)
			
			
	def CalcBoost(self, Action, mgW, phyW, ActOnMg, ActOnPhy):
		Adder = 0
		if (mgW > 0 and ActOnMg):
			Adder += Action.Power * self.TurboRate * mgW
		if (phyW > 0 and ActOnPhy):
			Adder += Action.Power * self.TurboRate * phyW
	def CalcStatCost(self, Action, Adder):
		if (Adder <= Action.Power):
			return 0
		if (Action.MPCost > 0 && self.TargetStat = Stats.MP)
			return int((Adder / Action.BasePower) * (1 + self.TurboRate) * Action.MPCost)
		
		
	def Clone(self):
		return copy.deepcopy(self)

class ActionReversalComponent(ActionModifierComponent):
	def __init__(self, Owner, ReflectMagic = True, ReflectSkills = False, DontReverseOnFlags = None, RandomUser = True):
		self.ReflectMg = ReflectMagic
		self.ReflectSkills = ReflectSkills
		self.DontReverseOnFlags = DontReverseOnFlags
		self.RandomUser = RandomUser
		ActionModifierComponent.__init__(self, Owner)
	
	def ModifyAction(self, Action, Mechanics):
		if (Action.Users.GetCount() > 0 and Action.Targets.GetCount() > 0 and ReversalCheck(Action, Mechanics)):
			for target in Action.Targets:
				if (target == Owner.GetHolder()):
					if (self.RandomUser):
						target.Character = Action.Users.GetCharacter(Mechanics.GetRandomInt(0, Action.Users.GetCount() - 1)
					else:
						target.Character = Action.Users.GetFirst()
					Action.SetReflected(True)
	def ReversalCheck(self, Action, Mechanics):
		Reverse = False
		if (Action != None):
			if ((self.ReflectMg && Action.IsMagic()) or (self.ReflectSkills && Action.IsSkill())):
				Reverse = True
				for flag in self.DontReverseOnFlags:
					if (Action.HasFlag(flag)):
						Reverse = False
						break
		return Reverse
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





