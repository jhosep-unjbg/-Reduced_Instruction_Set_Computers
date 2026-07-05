# Simulador de Arquitectura de Computadoras

## Descripción

El **Simulador de Arquitectura de Computadoras** es una aplicación desarrollada como proyecto universitario para simular el funcionamiento de diferentes arquitecturas de procesadores y comparar su rendimiento.

El sistema implementa una arquitectura **MVC (Model - View - Controller)** en **C++**, utilizando **Crow Framework** para exponer una API REST y un **Frontend Web** desarrollado con **HTML, CSS y JavaScript**.

La aplicación permite analizar arquitecturas Pipeline, Monociclo, RISC y CISC, además de realizar comparaciones de rendimiento, simulación de Pipeline Avanzado, generación de diagramas Gantt y exportación de resultados.

---

# Características

- Dashboard Web
- Simulación Pipeline
- Simulación Monociclo
- Simulación Arquitectura RISC
- Simulación Arquitectura CISC
- Comparación RISC vs CISC
- Comparación Pipeline vs Monociclo
- Pipeline Avanzado
- Simulación de Hazards
- Forwarding
- Flush
- Predictor dinámico de saltos (2 bits)
- Diagrama Gantt
- Historial dinámico
- Exportación CSV
- Exportación JSON
- Backend REST API

---

# Tecnologías utilizadas

## Backend

- C++17
- Crow Framework
- Asio Standalone
- Arquitectura MVC

## Frontend

- HTML5
- CSS3
- JavaScript
- Fetch API
- Live Server

## Persistencia

- CSV
- JSON

---

# Arquitectura del sistema

```
                FRONTEND

         HTML + CSS + JavaScript

                  │

              Fetch API

                  │

                  ▼

          Crow Framework REST API

                  │

                  ▼

            Controllers (MVC)

                  │

                  ▼

             Services (MVC)

                  │

                  ▼

              Models (MVC)

                  │

                  ▼

            ArchivoService

                  │

                  ▼

             CSV / JSON
```

---

# Estructura del proyecto

```
Arquitectura_procesador

│

├── backend

│   ├── controllers

│   ├── models

│   ├── services

│   ├── data

│   ├── vendor

│   ├── servidor.cpp

│   ├── servidor.h

│   ├── servidor_main.cpp

│   └── main.cpp

│

├── frontend

│   ├── css

│   ├── js

│   ├── pages

│   ├── components

│   ├── assets

│   └── index.html

│

├── docs

│

└── README.md
```

---

# Módulos implementados

## 1. Pipeline

Calcula:

- Ciclos
- Tiempo total
- Speedup
- Eficiencia

---

## 2. Monociclo

Calcula:

- Tipo R
- LW
- SW
- BEQ
- Periodo del reloj
- Frecuencia máxima
- Slack
- Eficiencia

---

## 3. Arquitectura RISC

Simula:

- Load Store
- Registros
- Memoria
- ALU
- Código Assembler
- Ejecución paso a paso

---

## 4. Arquitectura CISC

Simula:

- Registros
- Memoria
- ALU
- Código Assembler
- Ejecución paso a paso

---

## 5. Comparación RISC vs CISC

Compara:

- Número de instrucciones
- Accesos a memoria
- Complejidad
- Pipeline
- Resultado obtenido

---

## 6. Comparación Pipeline vs Monociclo

Calcula:

- Ciclos
- Tiempo
- Speedup
- Eficiencia
- Gráfico comparativo

---

## 7. Pipeline Avanzado

Incluye:

- RAW Hazards
- Forwarding
- Stall
- Flush
- Predictor de Saltos
- Pipeline real
- CPI
- Throughput
- Carta Gantt

---

# API REST

## Pipeline

```
POST /api/pipeline
```

---

## Monociclo

```
POST /api/monociclo
```

---

## RISC

```
POST /api/risc/simular
```

---

## CISC

```
POST /api/cisc/simular
```

---

## Comparación RISC vs CISC

```
GET /api/comparacion/risc-cisc
```

---

## Comparación Pipeline vs Monociclo

```
POST /api/comparacion-pipeline
```

---

## Pipeline Avanzado

```
POST /api/pipeline-avanzado
```

---

## Historial

```
GET /api/historial
```

---

## Exportar CSV

```
GET /api/exportar/csv
```

---

## Exportar JSON

```
GET /api/exportar/json
```

---

# Instalación

## 1. Clonar repositorio

```bash
git clone <repositorio>
```

---

## 2. Entrar al proyecto

```bash
cd Arquitectura_procesador/backend
```

---

## 3. Compilar

```bash
g++ servidor_main.cpp servidor.cpp ^
models/Pipeline.cpp ^
models/Monociclo.cpp ^
models/Risc.cpp ^
models/Cisc.cpp ^
models/Comparacionpipeline.cpp ^
models/PipelineGantt.cpp ^
services/Pipelineservice.cpp ^
services/Monocicloservice.cpp ^
services/Riscservice.cpp ^
services/Ciscservice.cpp ^
services/Comparacionpipelineservice.cpp ^
services/Archivoservice.cpp ^
-std=c++17 ^
-Ivendor/Crow/include ^
-o servidor.exe ^
-lws2_32 -lmswsock
```

---

## 4. Ejecutar Backend

```bash
./servidor.exe
```

Servidor:

```
http://127.0.0.1:18080
```

---

## 5. Ejecutar Frontend

Abrir la carpeta **frontend** con Visual Studio Code.

Ejecutar:

```
Live Server
```

Frontend:

```
http://127.0.0.1:5500
```

---

# Archivos generados

Durante la ejecución el sistema genera:

```
backend/data/historial.csv

backend/data/historial_general.csv

backend/data/resultado.csv

backend/data/resultado.json

backend/data/gantt.csv

backend/data/gantt.json
```

---

# Funcionalidades implementadas

- Backend REST con Crow
- Arquitectura MVC
- Historial dinámico
- Comunicación Frontend ↔ Backend
- Exportación CSV
- Exportación JSON
- Dashboard Web
- Visualización de resultados
- Simulación paso a paso

---

# Autor

**Jhosep Rodrigo Arocutipa Mamani**

Universidad Nacional Jorge Basadre Grohmann

Escuela Profesional de Ingeniería de Sistemas

Curso: Arquitectura de Computadoras

---

# Estado del proyecto

| Componente | Estado |
|------------|:------:|
| Backend MVC | ✅ |
| Crow REST API | ✅ |
| Frontend Web | ✅ |
| Pipeline | ✅ |
| Monociclo | ✅ |
| RISC | ✅ |
| CISC | ✅ |
| Comparaciones | ✅ |
| Pipeline Avanzado | ✅ |
| Historial | ✅ |
| Exportación CSV | ✅ |
| Exportación JSON | ✅ |
| Integración completa | ✅ |

## Proyecto Finalizado

**Versión:** 1.0

**Estado:** Finalizado y funcional.