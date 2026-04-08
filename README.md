
# SSD1306 I2C Driver pour STM32F103C8

Un driver I2C minimal et efficace pour contrôler les écrans OLED SSD1306 sur le microcontrôleur STM32F103C8.

## Description

Ce projet fournit une implémentation bas niveau du protocole I2C pour communiquer avec les écrans OLED SSD1306. Le code accède directement aux registres du STM32F103C8 sans dépendre de bibliothèques HAL complexes.

## Caractéristiques

- Implémentation bas niveau optimisée (registres directs)
- Support complet du protocole I2C en mode maître
- Gestion d'erreurs robuste avec codes de statut
- Détection d'appareil I2C
- Support des opérations de lecture/écriture combinées
- Simulation testable avec Wokwi

## Matériel

### Microcontrôleur
- **STM32F103C8** (ARM Cortex-M3)
- 64 KB RAM
- 256 KB Flash

### Écran
- **SSD1306 OLED** (128x64 pixels)
- Adresse I2C par défaut: `0x3C` ou `0x3D`

### Connexions I2C
| Signal | Broche STM32 | Broche SSD1306 |
|--------|-------------|---|
| SCL    | PB6         | SCL |
| SDA    | PB7         | SDA |
| GND    | GND         | GND |
| VCC    | 3.3V        | VCC |

## Architecture

```
.
├── bsp/                  # Board Support Package
│   ├── i2c.h            # En-têtes I2C avec définitions de registres
│   └── i2c.c            # Implémentation du driver I2C
├── src/
│   └── main.c           # Exemple d'utilisation
├── wokwi/               # Configuration de simulation
│   ├── diagram.json     # Schéma de simulation
│   └── wokwi.toml       # Configuration Wokwi
└── platformio.ini       # Configuration du projet PlatformIO
```

## Installation

### Prérequis
- [PlatformIO](https://platformio.org/) (VS Code extension recommandée)
- [Git](https://git-scm.com/)
- STM32CubeMX (optionnel, pour la génération de code)

### Cloner le projet
```bash
git clone <votre-repo>
cd ssd1306-driver-stm32
```

### Compiler
```bash
platformio run
```

### Compiler et télécharger sur le STM32
```bash
platformio run --target upload
```


## Simulation

### Avec Wokwi

Ce projet peut être simulé avec [Wokwi](https://wokwi.com/) directement depuis PlatformIO.

1. Créer un compte Wokwi (optionnel mais recommandé)
2. Dans VS Code avec PlatformIO:
   ```
   Ctrl+Alt+P → PlatformIO: Open Project
   ```
3. Lancer la simulation:
   ```
   platformio run --environment genericSTM32F103C8 -- --verbose
   ```

Le schéma de simulation est défini dans `wokwi/diagram.json` et montre le STM32F103C8 connecté à un écran SSD1306.

## Ressources

- [Datasheet STM32F103C8](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)
- [Datasheet SSD1306](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)
- [I2C Protocol Specification](https://www.nxp.com/docs/en/user-manual/UM10204.pdf)
- [PlatformIO Documentation](https://docs.platformio.org/)

## Licence

Ce projet est ouvert à la contribution. Consultez le fichier LICENSE pour plus de détails.

## 👤 Auteur

Développé pour explorer l'interfaçage bas niveau des périphériques sur STM32.

---

**Note**: Ce code est optimisé pour l'apprentissage et les projets embarqués. Pour les applications en production, considérez l'utilisation de la HAL STM32 officielle.
