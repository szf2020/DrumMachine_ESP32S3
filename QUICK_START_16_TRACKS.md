# 🚀 QUICK START - RED808 16 Tracks

## Pasos Rápidos

### 1. Preparar Samples (5 minutos)

```bash
# Crear estructura
mkdir samples_raw
cd samples_raw
mkdir BD SD CH OH CP CB RS CL MA CY TM1 TM2 TM3 HC LC PERC

# Copiar tus .wav a cada carpeta
# Puedes copiar muchos, el script filtrará automáticamente

# Volver y ejecutar filtrado
cd ..
python prepare_samples_16tracks.py
```

**Resultado esperado:**
```
✓ BD: 6 samples (0.45 MB)
✓ SD: 6 samples (0.52 MB)
...
Total: 96 samples, 5.2 MB
```

### 2. Subir a ESP32 (2 minutos)

```bash
# Subir filesystem (samples + web)
pio run --target uploadfs

# Compilar y subir firmware
pio run --target upload

# Abrir monitor
pio device monitor
```

### 3. Conectar y Probar (1 minuto)

1. **WiFi**: Conectar a `RED808` (password: `red808esp32`)
2. **Browser**: Abrir `http://192.168.4.1`
3. **Probar**: Click en pads o usar teclado `1-9,0,Q-Y`

## ⌨️ Keyboard Shortcuts

```
PADS:
1 2 3 4 5 6 7 8 9 0 Q W E R T Y
│ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
BD SD CH OH CP CB RS CL MA CY TM1 TM2 TM3 HC LC PERC

CONTROLES:
SPACE  →  Play/Pause
[  ]   →  BPM +5/-5
-  +   →  Volume +5/-5
```

## ✅ Verificación Rápida

- [ ] 16 pads visibles y funcionando
- [ ] Sequencer 16×16 steps visible
- [ ] Tremolo al mantener tecla (sin errores)
- [ ] Device info muestra stats
- [ ] Modo color/mono funciona
- [ ] Visualizers actualizan
- [ ] FX afectan el sonido

## 🆘 Troubleshooting

### Error: "Too many messages queued"
✅ **SOLUCIONADO** - Tremolo optimizado a 180ms

### No se ven los pads
- Verificar que `uploadfs` completó correctamente
- Borrar caché del browser (Ctrl+Shift+R)

### No suenan algunos pads
- Verificar que las carpetas tengan .wav
- Revisar Serial Monitor para ver qué se cargó

### Grid muy pequeño en tablet
- Usar landscape (horizontal)
- Zoom del browser si es necesario

## 📱 Dispositivos Testeados

- ✅ Desktop (1920×1080) - Perfecto
- ✅ Tablet (1024×768) - Optimizado
- ⚠️ Mobile (<768px) - Funcional pero compacto

## 🎛️ Features

- **16 Pads** con tremolo automático
- **16×16 Sequencer** con 16 patterns
- **3-Second Hold Loop** por track
- **6 Audio FX** en tiempo real
- **Spectrum + Waveform** visualizers
- **Keyboard Control** completo
- **Responsive Design** tablet/desktop
- **Mono/Color Mode** toggle

## 📖 Docs Completos

- `ESTRUCTURA_16_TRACKS.md` - Arquitectura detallada
- `CHANGELOG_16_TRACKS.md` - Cambios implementados
- `README.md` - Documentación original

---

**¡Listo para usar!** 🎵
