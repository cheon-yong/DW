
#pragma once

#include "GameplayTagContainer.h"

// Actor
#define DWTAG_ACTOR_ROTATE FGameplayTag::RequestGameplayTag(FName("Actor.Action.Rotate"))
#define DWTAG_ACTOR_ISROTATING FGameplayTag::RequestGameplayTag(FName("Actor.State.IsRotating"))

#define DWTAG_DATA_DAMAGE FGameplayTag::RequestGameplayTag(FName("Data.Damage"))

// Character
#define DWTAG_CHARACTER_ISDEAD FGameplayTag::RequestGameplayTag(FName("Character.State.IsDead"))
#define DWTAG_CHARACTER_INVINSIBLE FGameplayTag::RequestGameplayTag(FName("Character.State.Invinsible"))
		
// GameplayCue
#define DWTAG_GAMEPLAYCUE_CHARACTER_ATTACK FGameplayTag::RequestGameplayTag(FName("GameplayCue.Character.Attack"))
#define DWTAG_GAMEPLAYCUE_CHARACTER_ATTACKHIT FGameplayTag::RequestGameplayTag(FName("GameplayCue.Character.AttackHit"))
#define DWTAG_GAMEPLAYCUE_CHARACTER_DAMAGETAKEN FGameplayTag::RequestGameplayTag(FName("GameplayCue.Character.DamageTaken"))
		
// Event
// Event.Character
#define DWTAG_EVENT_CHARACTER_WEAPONEQUIP FGameplayTag::RequestGameplayTag(FName("Event.Character.Weapon.Equip"))
#define DWTAG_EVENT_CHARACTER_WEAPONUNEQUIP FGameplayTag::RequestGameplayTag(FName("Event.Character.Weapon.Unequip"))

// Event.Monster
#define DWTAG_EVENT_MONSTER_ATTACK FGameplayTag::RequestGameplayTag(FName("Event.Monster.Attack"))

// Game
#define DWTAG_GAME_STATE_READY FGameplayTag::RequestGameplayTag(FName("Game.State.Ready"))
#define DWTAG_GAME_STATE_PLAYING FGameplayTag::RequestGameplayTag(FName("Game.State.Playing"))
#define DWTAG_GAME_STATE_DEFEATED FGameplayTag::RequestGameplayTag(FName("Game.State.Defeated"))
#define DWTAG_GAME_STATE_CLEAR FGameplayTag::RequestGameplayTag(FName("Game.State.Clear"))