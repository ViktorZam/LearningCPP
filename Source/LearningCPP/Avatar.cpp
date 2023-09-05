// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "MyHUD.h"
#include "PickupItem.h"
#include "Spell.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// применяем вектор отбрасывания
	AddMovementInput(knockback, 1.f);
	// делим пополам объём отбрасывания каждый кадр
	knockback *= 0.5f;


}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);
	PlayerInputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
	PlayerInputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);
	PlayerInputComponent->BindAction("MouseClickedRMB", IE_Pressed, this,&AAvatar::MouseRightClicked);

	// остальная часть SetupPlayerInputComponent такая же как до этого
}


void AAvatar::MoveForward(float amount)
{
	if (inventoryShowing)
	{
		return; // когда мой инвентарь показывается,
		// игрок не может двигаться
	}
	// Не вводите тело этой функции, если контроллер
	// ещё не установлен или если сумма для движения равна 0
	if (Controller && amount)
	{
		FVector fwd = GetActorForwardVector();
		// мы вызываем AddMovementInput, чтобы собственно двигать
		// игрока `суммой` в направлениях `fwd`
		AddMovementInput(fwd, amount);
	}
}
void AAvatar::MoveRight(float amount)
{
	if (inventoryShowing)
	{
		return; // когда мой инвентарь показывается,
		// игрок не может двигаться
	}
	if (Controller && amount)
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}
}

void AAvatar::Yaw(float amount)
{
	if (inventoryShowing)
	{
		// Когда инвентарь показан,
		// передаём вводные в HUD
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseMoved();

		return; // когда мой инвентарь показывается,
		// игрок не может двигаться
	}
	AddControllerYawInput(200.f * amount * GetWorld() -> GetDeltaSeconds());
}
void AAvatar::Pitch(float amount)
{
	if (inventoryShowing)
	{
		return; // когда мой инвентарь показывается,
		// игрок не может двигаться
	}
	AddControllerPitchInput(200.f * amount * GetWorld() -> GetDeltaSeconds());
}

void AAvatar::ToggleInventory()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, "Showinginventory…");
	}
	// Получаем контроллер и HUD
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	// Если инвентарь отображается, то прекращаем отображать его.
	if (inventoryShowing)
	{
		hud->widgets.Empty();
		inventoryShowing = false;
		PController->bShowMouseCursor = false;
		return;
	}
	// Иначе отображаем инвентарь игрока
	inventoryShowing = true;
	PController->bShowMouseCursor = true;
	for (TMap<FString, int>::TIterator it = Backpack.CreateIterator(); it; ++it)
	{
		// Комбинируем имя предмета с количеством, то есть Cow x 5
		FString fs = it->Key + FString::Printf(TEXT(" x %d"), it->Value);
		UTexture2D* tex;
		if (Icons.Find(it->Key)) 
		{
			tex = Icons[it->Key];
			if (Spells[it->Key])
			{
				hud->addWidget(Widget(Icon(fs, tex), Spells[it->Key]));
			}
			else
			{
				hud->addWidget(Widget(Icon(fs, tex)));
			}
			Widget w(Icon(fs, tex));
			w.bpSpellClass = Spells[it->Key];
		}
			
	}

}

void  AAvatar::Pickup(APickupItem* item)
{
	if (Backpack.Find(item->Name))
	{
		// предмет уже был в рюкзаке… увеличиваем его количество
		Backpack[item->Name] += item->Quantity;
	}
	else
	{
		// предмета не было в рюкзаке, сейчас добавляем его туда
		Backpack.Add(item->Name, item->Quantity);
		// записываем ссылку на текстуру, когда предмет взят первый раз
		Icons.Add(item->Name, item->Icon);
	}
	if (item->Spell)
	{
		Spells.Add(item->Name, item->Spell);
	}
	
}

void AAvatar::MouseClicked()
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->PController = PController;
	hud->MouseClicked();
}

float AAvatar::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	Hp = Hp - DamageAmount;
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	knockback = GetActorLocation() - DamageCauser->GetActorLocation();
	knockback.Normalize();
	knockback *= DamageAmount * 500; // отрасывание пропорциональное урону
	return DamageAmount;
}

void AAvatar::CastSpell(UClass* bpSpell)
{
	// создаём экземпляр заклинания и прикрепляем его к персонажу
	ASpell* spell = GetWorld()->SpawnActor<ASpell>(bpSpell, FVector(0), FRotator(0));
	if (spell)
	{
		spell->SetCaster(this);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString("заклинание не послать ") + bpSpell->GetName() );
	}
}

void AAvatar::MouseRightClicked()
{
	if (inventoryShowing)
	{
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseRightClicked();
	}
}
