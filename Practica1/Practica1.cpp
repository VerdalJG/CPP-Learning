#include <iostream>

#define MASK_BULLETS 0x000000FF
#define MASK_MAX_BULLETS 0x00FF0000
#define MASK_INFINITE_BULLETS 0x00000002

unsigned int NumberOfBullets(unsigned int _uSaveData)
{
    unsigned int iBulletHex = _uSaveData >> 16;
    iBulletHex &= MASK_BULLETS;
    return iBulletHex;
}

void AddBullets(unsigned int& _uSaveData_, unsigned int _bulletsToAdd)
{
    if (NumberOfBullets(_uSaveData_) + _bulletsToAdd <= 255)
    {
        _uSaveData_ += _bulletsToAdd << 16;
    }
    else
    {
        _uSaveData_ |= MASK_MAX_BULLETS;
    }
}

void ToggleInfiniteBullets(unsigned int& _uSaveData_)
{
    _uSaveData_ ^= MASK_INFINITE_BULLETS;
}

bool IsInfiniteBulletsActive(unsigned int _uSaveData)
{
    return _uSaveData & MASK_INFINITE_BULLETS;
}

int main()
{
    // 55 lives
    // 142 bullets
    // 3 companions
    // Berserker: false
    // Shield: false
    // Infinite Bullets: false
    // Invulnerable: true

    unsigned int uSaveData = 0x378E3001;
    printf("Number of Bullets: %d\n", NumberOfBullets(uSaveData));
    AddBullets(uSaveData, 10);
    printf("Number of Bullets after adding: %d\n", NumberOfBullets(uSaveData));

    printf("Infinite bullets: %s\n", IsInfiniteBulletsActive(uSaveData) ? "TRUE" : "FALSE");

    ToggleInfiniteBullets(uSaveData);
    printf("Infinite bullets: %s\n", IsInfiniteBulletsActive(uSaveData) ? "TRUE" : "FALSE");

    ToggleInfiniteBullets(uSaveData);
    printf("Infinite bullets: %s\n", IsInfiniteBulletsActive(uSaveData) ? "TRUE" : "FALSE");


}


