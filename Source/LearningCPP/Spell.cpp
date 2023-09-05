// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"
#include "Monster.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"


// Sets default values
ASpell::ASpell(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProxBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
	Particles = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this,TEXT("ParticleSystem"));
	// Particles �������� �������� �����������, � ProxBox
	// �������� �������� �������� ������� ������ - Particle.
	// ���� �� ��� ��� ������ ������, �� ��������������� ProxBox
	// ����� �������������� �� Particles, ���� �� �� �����
	RootComponent = Particles;
	ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Duration = 3; // �����������������
	DamagePerSecond = 1; // ���� �� �������
	TimeAlive = 0; // ����� �����

}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// ���� ProxBox ��� ���� ������� � ������.
	TArray<AActor*> actors;
	ProxBox->GetOverlappingActors(actors);
	// ������� ���� ������� ������ ����������� � ������� �����
	for (int c = 0; c < actors.Num(); c++)
	{
		// ����� �� ��������� ����, ��� �������� ����������
		if (actors[c] != Caster)
		{
			// ������� ���� ������, ���� ���� ������������ �
			// �������� ����������� ������.
			// ����� �������, ����� �� �����, ���� ����� ������
			// ����������� � SightSphere �������
			AMonster* monster = Cast<AMonster>(actors[c]);
			//ProxBox->IsOverlappingComponent
			//if (monster && ProxBox->IsOverlappingComponent((UPrimitiveComponent*)monster->GetCapsuleComponent()))
			if (monster && ProxBox->IsOverlappingComponent(monster->GetCapsuleComponent()))
			{
				monster->TakeDamage(DamagePerSecond * DeltaTime, FDamageEvent(), 0, this);
			}
			// ����� �������� ���� ������ ����� ������, ���������� ����������� ���������
			// �����...
		}
	}
	TimeAlive += DeltaTime;
	if (TimeAlive > Duration)
	{
		Destroy();
	}
}

void ASpell::SetCaster(AActor* caster)
{
	Caster = caster;
	AttachToComponent(caster->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

