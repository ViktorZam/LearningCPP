// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"

// Sets default values
APickupItem::APickupItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Name = "UNKNOWN ITEM"; // ������������ ������Ҕ
		Quantity = 0;
	// ����� ������ Unreal
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	// ������ �������� �������� Mesh
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);
	// ����� ��� ��� ������� APickupItem::Prox(), ����� ���
	// ����� �������� ������� ������������ � ������ �������.
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this,&APickupItem::Prox);
	ProxSphere->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // ����� �����!
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupItem::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ���� �����, � ������� ��������� �����������, �� �������� �������,
// �� ������ ������ ���������
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	// �������� ������ �� ������ ������, ����� ���� ��� �������
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// ��������� ������ ��������� �������
	// �������� �� �������� ����� this!
	// ��� ��, ��� _this_ Pickup ����� ��������� �� ���� ����.
	avatar->Pickup(this);
	// �������� ������ �� ����������
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	// �������� ������ �� HUD �� �����������
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->addMessage(Message(FString("Picked up ") + FString::FromInt(Quantity) + FString(" ") + Name, 5.f, FColor::White, Icon));
	Destroy();
}