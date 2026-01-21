# Estructura de 16 Tracks - RED808

## Carpetas de Instrumentos

El sistema ahora soporta **16 pistas/instrumentos simultáneos**. Cada carpeta debe contener samples `.wav` del instrumento correspondiente.

### Estructura de Carpetas en `data/`

```
data/
├── BD/       # Bass Drum (Bombo) - 808 kick drums
├── SD/       # Snare Drum (Caja) - 808 snare drums  
├── CH/       # Closed Hi-Hat - 808 closed hi-hats
├── OH/       # Open Hi-Hat - 808 open hi-hats
├── CP/       # Clap (Palmas) - 808 hand claps
├── CB/       # Cowbell (Cencerro) - 808 cowbell
├── RS/       # Rimshot (Aro) - 808 rimshot
├── CL/       # Claves - 808 claves
├── MA/       # Maracas - 808 maracas
├── CY/       # Cymbal (Platillo) - 808 cymbal
├── TM1/      # Tom 1 (Agudo) - high tom
├── TM2/      # Tom 2 (Medio) - mid tom
├── TM3/      # Tom 3 (Grave) - low tom
├── HC/       # Hand Clap - alternative clap samples
├── LC/       # Low Conga - 808 conga low
└── PERC/     # Percussion - otros samples de percusión
```

## Limitaciones

- **Máximo 5-6 samples por carpeta** (para optimizar memoria)
- **Tamaño total: ~5-6 MB** (límite de PSRAM para samples)
- **Formato**: WAV 16-bit mono/stereo, 44.1kHz recomendado

## Proceso de Preparación

### 1. Organiza tus samples

Crea una carpeta `samples_raw/` con subcarpetas para cada instrumento:

```bash
samples_raw/
├── BD/
│   ├── kick_808_01.wav
│   ├── kick_808_02.wav
│   └── ...
├── SD/
│   ├── snare_808_01.wav
│   ├── snare_808_02.wav
│   └── ...
└── ...
```

### 2. Ejecuta el script de filtrado

```bash
python prepare_samples_16tracks.py
```

El script:
- Selecciona automáticamente los mejores samples (más pequeños primero)
- Limita a máximo 6 samples por instrumento
- Verifica que el total no exceda 5-6 MB
- Copia y renombra los samples a `data/`

### 3. Verifica el resultado

```
✓ BD: 6 samples (0.45 MB)
✓ SD: 6 samples (0.52 MB)
✓ CH: 5 samples (0.23 MB)
...
Total: 96 samples, 5.2 MB
```

### 4. Sube a ESP32

```bash
pio run --target uploadfs
```

## Mapeo de Teclado

Con 16 pads, el mapeo de teclado es:

```
1  2  3  4  5  6  7  8  9  0  Q  W  E  R  T  Y
│  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
BD SD CH OH CP CB RS CL MA CY TM1 TM2 TM3 HC LC PERC
```

**Controles adicionales:**
- `SPACE`: Play/Pause
- `[` / `]`: BPM +5 / -5
- `-` / `+`: Volume -5 / +5

## Sequencer Grid

El sequencer muestra **16 tracks × 16 steps**:

```
BD   ▓ ░ ░ ░ ▓ ░ ░ ░ ▓ ░ ░ ░ ▓ ░ ░ ░
SD   ░ ░ ░ ░ ▓ ░ ░ ░ ░ ░ ░ ░ ▓ ░ ░ ░
CH   ░ ▓ ░ ▓ ░ ▓ ░ ▓ ░ ▓ ░ ▓ ░ ▓ ░ ▓
...  (16 tracks total)
```

El diseño es **responsive** y se adapta a tablets y laptops.

## Web Interface

### Device Info Section

La nueva sección muestra:
- Sampler: ESP32-S3 @ 240MHz
- Sample Rate: 44.1kHz 16-bit
- Polyphony: 16 voices
- Tracks: 16 tracks × 16 steps
- Samples: Count (ej. 96 loaded)
- Memory: Usage (ej. 5.2 MB / 8 MB PSRAM)

### Tamaños Responsive

- **Desktop**: Grid completo 16×16
- **Tablet**: Grid compacto, pads más pequeños
- **Mobile**: Vista optimizada vertical

## Backend Changes

### KitManager

El KitManager cargará samples de las 16 carpetas:

```cpp
const char* folders[16] = {
    "/BD", "/SD", "/CH", "/OH", "/CP", "/CB", "/RS", "/CL",
    "/MA", "/CY", "/TM1", "/TM2", "/TM3", "/HC", "/LC", "/PERC"
};
```

### AudioEngine

- Polyphony: 16 voces (ya implementado)
- Sample rate: 44.1kHz 16-bit stereo
- Buffer: 128 samples × 4 buffers DMA

### Memory Budget

```
PSRAM Total:      8 MB
Samples:          ~5.5 MB (96 samples × ~60KB avg)
Audio buffers:    ~2 KB (128 × 16-bit × 2 channels × 4)
Stack/Heap:       ~2.5 MB available
```

## Notas Técnicas

1. **Polifonía**: 16 voces simultáneas permite que todas las pistas suenen a la vez
2. **Latencia**: Protocolo binario WebSocket para triggers de baja latencia
3. **CPU**: ~40-50% usage en ESP32-S3 dual-core @ 240MHz
4. **WiFi**: Access Point mode, no requiere router

## Recomendaciones de Samples

- **BD**: Variedad de kicks (sub, punch, 808 classic)
- **SD**: Snares con diferentes tones
- **CH/OH**: Hi-hats con decaimiento variable
- **CP**: Claps naturales y sintéticos
- **Toms**: Tuneados a diferentes frecuencias (high/mid/low)
- **PERC**: Samples experimentales, FX, shakers

## Próximas Mejoras

- [ ] Pattern save/load to EEPROM
- [ ] Per-track volume controls
- [ ] Send/Return FX (reverb, delay)
- [ ] MIDI input support
- [ ] Sample preview in web interface
