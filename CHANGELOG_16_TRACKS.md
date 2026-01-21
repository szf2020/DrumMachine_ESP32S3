# RED808 - Actualización a 16 Tracks

## 🎯 Resumen de Cambios

Se ha actualizado completamente el sistema de 8 a **16 pistas/tracks simultáneos** con diseño responsive y gestión automática de samples.

## 📋 Cambios Implementados

### 1. **Backend (ESP32-S3)**

#### KitManager.cpp
- ✅ **scanKits()** actualizado para escanear 16 carpetas automáticamente
- ✅ Carga el primer sample de cada carpeta: `BD, SD, CH, OH, CP, CB, RS, CL, MA, CY, TM1, TM2, TM3, HC, LC, PERC`
- ✅ Kit único "RED808 16-Track" con todos los instrumentos disponibles
- ✅ Logs mejorados con emojis para mejor visualización

**Carpetas de instrumentos:**
```
/BD   - Bass Drum (Bombo)
/SD   - Snare Drum (Caja)
/CH   - Closed Hi-Hat
/OH   - Open Hi-Hat
/CP   - Clap (Palmas)
/CB   - Cowbell (Cencerro)
/RS   - Rimshot (Aro)
/CL   - Claves
/MA   - Maracas
/CY   - Cymbal (Platillo)
/TM1  - Tom 1 (Agudo)
/TM2  - Tom 2 (Medio)
/TM3  - Tom 3 (Grave)
/HC   - Hand Clap
/LC   - Low Conga
/PERC - Percussion (otros)
```

### 2. **Frontend (Web Interface)**

#### index.html
- ✅ Actualizado footer con info del dispositivo
- ✅ Nueva sección "Device Info" con 6 stats:
  - Sampler: ESP32-S3 @ 240MHz
  - Sample Rate: 44.1kHz 16-bit
  - Polyphony: 16 voices
  - Tracks: 16 tracks × 16 steps
  - Samples: Count dinámico
  - Memory: Usage dinámico
- ✅ Keyboard shortcuts actualizados en la leyenda

#### app.js
- ✅ **padNames[]** expandido a 16 nombres
- ✅ **createPads()** genera 16 pads en lugar de 8
- ✅ **createSequencer()** crea grid de 16×16 steps
- ✅ **Keyboard controls** actualizados:
  - `1-9, 0, Q, W, E, R, T, Y` → Pads 1-16 con tremolo
  - `SPACE` → Play/Pause
  - `[` / `]` → BPM +5/-5
  - `-` / `+` → Volume +5/-5
- ✅ Tremolo optimizado a 180ms para evitar saturación WebSocket

#### style.css
- ✅ **Pads grid**: 4×4 compacto con max-width 800px
- ✅ **Sequencer grid**: 16 tracks × 16 steps con gap reducido (2px)
- ✅ **Device Info section**: Estilo profesional con soporte mono-mode
- ✅ **Media queries responsive**:
  - **Tablets (768-1024px)**: Grid optimizado, font-size reducido
  - **Mobile (<768px)**: 2 columnas pads, sequencer ultra-compacto, visualizers ocultos

### 3. **Herramientas**

#### prepare_samples_16tracks.py
- ✅ Script Python para filtrar samples automáticamente
- ✅ Límite de 5-6 samples por instrumento
- ✅ Control de tamaño total (máximo 5-6 MB)
- ✅ Selección inteligente (archivos más pequeños primero)
- ✅ Estadísticas detalladas al finalizar

**Uso:**
```bash
python prepare_samples_16tracks.py
```

### 4. **Documentación**

#### ESTRUCTURA_16_TRACKS.md
- ✅ Guía completa de la nueva arquitectura
- ✅ Mapeo de carpetas y nombres de instrumentos
- ✅ Instrucciones de preparación de samples
- ✅ Keyboard shortcuts reference
- ✅ Memory budget y especificaciones técnicas

## 🎮 Nuevo Mapeo de Teclado

```
Tecla → Pad → Instrumento
-------------------------
  1   →  0  → KICK
  2   →  1  → SNARE
  3   →  2  → CLHAT (Closed Hi-Hat)
  4   →  3  → OPHAT (Open Hi-Hat)
  5   →  4  → CLAP
  6   →  5  → COW (Cowbell)
  7   →  6  → RIM (Rimshot)
  8   →  7  → CLAV (Claves)
  9   →  8  → MARAC (Maracas)
  0   →  9  → CYMBAL
  Q   → 10  → TOM1 (Agudo)
  W   → 11  → TOM2 (Medio)
  E   → 12  → TOM3 (Grave)
  R   → 13  → HCLAP (Hand Clap)
  T   → 14  → CONGA
  Y   → 15  → PERC (Percussion)
```

**Controles globales:**
- `SPACE` → Toggle Play/Pause
- `[` / `]` → BPM +5/-5
- `-` / `+` → Volume +5/-5

## 📱 Diseño Responsive

### Desktop (>1024px)
- Grid completo 16×16 visible
- Pads 4×4 tamaño normal
- Visualizers a tamaño completo
- Toda la información visible

### Tablet (768-1024px)
- Grid 16×16 compacto
- Pads 4×4 reducidos (gap 8px)
- Sequencer con label de 45px
- Font-size reducido (9px)
- Visualizers a 150px altura

### Mobile (<768px)
- Pads 2×2 (mitad)
- Sequencer ultra-compacto (label 35px)
- Steps mínimos (12×12px)
- Visualizers ocultos (ahorrar espacio)
- Info en 1 columna

## 🔧 Próximos Pasos

### Para el usuario:

1. **Preparar samples**:
   ```bash
   # Crear carpeta con tus samples
   mkdir samples_raw
   cd samples_raw
   mkdir BD SD CH OH CP CB RS CL MA CY TM1 TM2 TM3 HC LC PERC
   
   # Copiar tus .wav a cada carpeta
   # ...
   
   # Ejecutar script de filtrado
   cd ..
   python prepare_samples_16tracks.py
   ```

2. **Compilar y subir**:
   ```bash
   # Subir filesystem
   pio run --target uploadfs
   
   # Compilar y subir firmware
   pio run --target upload
   
   # Monitor serial
   pio device monitor
   ```

3. **Probar en web**:
   - Conectar a WiFi "RED808"
   - Abrir http://192.168.4.1
   - Probar los 16 pads (click, touch, keyboard)
   - Verificar sequencer 16×16
   - Confirmar info del dispositivo

### Testing checklist:

- [ ] 16 pads responden correctamente
- [ ] Tremolo funciona sin error "Too many messages"
- [ ] Sequencer muestra 16 tracks × 16 steps
- [ ] Keyboard controls 1-9,0,Q-Y funcionan
- [ ] Device Info muestra stats correctos
- [ ] Diseño responsive en tablet/mobile
- [ ] Modo monocromo se ve bien
- [ ] Audio FX funcionan con 16 tracks
- [ ] Visualizers actualizan correctamente
- [ ] Memoria PSRAM suficiente (~5.5MB samples)

## 📊 Especificaciones Técnicas

```
CPU:              ESP32-S3 Dual-Core @ 240MHz
RAM:              512 KB SRAM
PSRAM:            8 MB (5.5MB para samples)
Audio:            I2S 44.1kHz 16-bit stereo
Polyphony:        16 voices simultaneous
Tracks:           16 tracks × 16 steps
Patterns:         16 patterns
Samples/Track:    1-6 samples por instrumento
Total Samples:    ~96 samples (promedio 6 por track)
WebSocket:        Binary protocol para baja latencia
Tremolo Rate:     180ms (5.5 triggers/seg)
FX Chain:         Filter → BitCrush → Distortion → SampleRate
Visualizers:      64-band Spectrum + 128-sample Waveform @ 20fps
Fonts:            Rajdhani 700, Roboto Mono 500-700
```

## 🐛 Problemas Conocidos Solucionados

1. ~~"Too many messages queued"~~ → ✅ Tremolo reducido a 180ms
2. ~~Volume no afectaba audio~~ → ✅ Master volume implementado
3. ~~Keyboard solo 8 pads~~ → ✅ Expandido a 16 con nuevo mapeo
4. ~~No info del dispositivo~~ → ✅ Nueva sección agregada
5. ~~No responsive en tablets~~ → ✅ Media queries completas

## 📝 Notas Finales

- El backend ya tenía soporte para 16 tracks (MAX_TRACKS = 16 en headers)
- Solo se actualizó KitManager para escaneo automático de carpetas
- El frontend se actualizó completamente para UI de 16 tracks
- Tremolo optimizado para evitar saturación WebSocket
- Diseño 100% responsive para todos los dispositivos
- Documentación completa en ESTRUCTURA_16_TRACKS.md

---

**Versión:** 2.0.0 (16-Track Edition)  
**Fecha:** Enero 2026  
**Estado:** ✅ Listo para testing en hardware
