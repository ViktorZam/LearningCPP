// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Avatar.h"
#include "AMeleeWeapon.h"
#include "Bullet.h"

// Sets default values
AMonster::AMonster(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 20; // ��������
	HitPoints = 100; // ��������
	Experience = 0; // ����
	BPLoot = NULL; // ������
	BaseAttackDamage = 1; // ���� ������� �����
	AttackTimeout = 1.5f; // ������������ �����
	TimeSinceLastStrike = 0; // ������ ������� � ���������� �����
	SightSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,TEXT("SightSphere"));
	SightSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	AttackRangeSphere = ObjectInitializer.CreateDefaultSubobject <USphereComponent>(this,TEXT("AttackRangeSphere"));
	AttackRangeSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// ������ ��������� ������, ���� �������� ��� ������
	if (BPMeleeWeapon)
	{
		MeleeWeapon = GetWorld()->SpawnActor<AAMeleeWeapon>(BPMeleeWeapon, FVector(),FRotator());
		if (MeleeWeapon)
		{
			
			// ���������, ��� ����������� ������
			// ��� ������!
			MeleeWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "RightHandSocket");
			Cast<AAMeleeWeapon>(MeleeWeapon)->WeaponHolder = this;
			
		}
	}
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// ������� ������� �� ������
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!avatar) return;
	FVector playerPos = avatar->GetActorLocation();
	FVector toPlayer = playerPos - GetActorLocation();
	float distanceToPlayer = toPlayer.Size();
	// ���� ����� �� ��������� SightSphere �������,
	// ������������
	if (distanceToPlayer > SightSphere->GetScaledSphereRadius())
	{
		// ���� ����� ��� OS, �� ������ �� ����� �� ��� �������
		return;
	}
	toPlayer /= distanceToPlayer; // ����������� ������
	// ��������� ����� � ����
	// ��������� ������� ��� ������������� ����,
	// ��� ������� � ���������� ������ `toPlayer`
	FRotator toPlayerRotation = toPlayer.Rotation();
	toPlayerRotation.Pitch = 0; // 0 �� �������
	RootComponent->SetWorldRotation(toPlayerRotation);
	if (isInAttackRange(distanceToPlayer) || (isInSightRange(distanceToPlayer) && BPBullet))
	{
		// ��������� �����
		CheckTimeAttack(avatar, DeltaTime);
		
	}
	
	else
	{
		// �� � ���� ������������ �����, ����� ��� � ������
		AddMovementInput(toPlayer, Speed * DeltaTime);
	}

}

void AMonster::CheckTimeAttack(AAvatar* avatar, float DeltaTime)
{
	if (!TimeSinceLastStrike)
	{
		Attack(avatar);
	}
	TimeSinceLastStrike += DeltaTime;
	if (TimeSinceLastStrike > AttackTimeout)
	{
		TimeSinceLastStrike = 0;
	}
	return; // ������ ������ �� ������


}



// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::SwordSwung()
{
	if (MeleeWeapon)
	{
		Cast<AAMeleeWeapon>(MeleeWeapon)->Swing();
	}
}

void AMonster::Attack(AActor* thing)
{
	if (MeleeWeapon)
	{
		// ��� ��� ������� ���������� �������, ����
		// ���������� ������ ������������
		(Cast<AAMeleeWeapon>(MeleeWeapon))->Swing();
	}
	else if (BPBullet)
	{
		// If a blueprint for a bullet to use was assigned,
		// then use that. Note we wouldn't execute this code
		// bullet firing code if a MeleeWeapon was equipped
		FVector fwd = GetActorForwardVector();
		FVector nozzle = GetMesh()->GetBoneLocation("Hand_R");
		nozzle += fwd * 155;// ������� � �� �������, ��� ���
		// ��� �� ������������ � ������� �������
		FVector toOpponent = thing->GetActorLocation() - nozzle;
		toOpponent.Normalize();
		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(BPBullet, nozzle, RootComponent->GetComponentRotation());
		if (bullet)
		{
			//bullet->Firer = this;
			bullet->ProxSphere->AddImpulse(fwd * BulletLaunchImpulse);
			GEngine->AddOnScreenDebugMessage(0, 1.f,FColor::Yellow, "Bullet");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 5.f,
				FColor::Yellow, "monster: no bullet actor could be spawned. is the bullet overlapping something?"
			);
		}
	}
}


float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator,
							AActor* DamageCauser)
{
	
	HitPoints = FMath::Clamp((HitPoints - DamageAmount), 0, 100);
	if (HitPoints == 0)
	{
		TArray<AActor*> AttachedActors;
		GetAttachedActors(AttachedActors);
		
		for (TArray<AActor*>::TIterator it = AttachedActors.CreateIterator(); it; ++it)
		{
			AttachedActors[it.GetIndex()]->Destroy();
		}
		Destroy();
	}
	return 0;
}

