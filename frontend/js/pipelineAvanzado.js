"use strict";

/* =========================================================
   PIPELINE AVANZADO
   Hazards RAW + Forwarding + Stalls + Flush
   Predictor dinámico de saltos de 2 bits
========================================================= */

const CONFIG_PIPELINE_AVANZADO = {
  cantidadInstrucciones: 5,
  etapas: 5,
  tiempoCiclo: 2,
  unidadTiempo: "ns",
  forwarding: true,
  penalizacionDatos: 2,
  penalizacionControl: 2,
  estadoPredictor: "ST",

  instrucciones: [
    "ADD R1,R2,R3",
    "BEQ R1,R2,L1 T",
    "ADD R4,R5,R6",
    "BNE R4,R7,L2 N",
    "J L3 T"
  ].join("\n")
};


/* =========================================================
   INICIALIZACIÓN
========================================================= */

function initPipelineAvanzado() {
  const body = document.body;

  if (!body || body.dataset.page !== "pipeline-avanzado") {
    return;
  }

  const textarea = document.getElementById(
    "instruccionesPipelineAvanzado"
  );

  if (textarea && !textarea.dataset.listenerAsignado) {
    textarea.addEventListener("input", actualizarCantidadInstrucciones);
    textarea.dataset.listenerAsignado = "true";
  }

  actualizarCantidadInstrucciones();
}


function actualizarCantidadInstrucciones() {
  const textarea = document.getElementById(
    "instruccionesPipelineAvanzado"
  );

  const inputCantidad = document.getElementById(
    "cantidadInstrucciones"
  );

  if (!textarea || !inputCantidad) {
    return;
  }

  const instrucciones = obtenerLineasValidas(textarea.value);

  inputCantidad.value = instrucciones.length;
}


/* =========================================================
   EJECUTAR SIMULACIÓN
========================================================= */
async function ejecutarPipelineAvanzado() {
  try {
    const configuracion = obtenerConfiguracion();

    validarConfiguracion(configuracion);

    const instrucciones = configuracion.instrucciones.map(
      (texto, indice) => analizarInstruccion(texto, indice)
    );
    const backend = await postData("/api/pipeline-avanzado", {
  etapas: configuracion.etapas,
  tiempoCiclo: configuracion.tiempoCiclo,
  forwarding: configuracion.forwarding,
  penalizacionDatos: configuracion.penalizacionDatos,
  penalizacionControl: configuracion.penalizacionControl,
  estadoPredictor: configuracion.estadoPredictor,
  instrucciones: configuracion.instrucciones
});

    const resultadoRiesgos = analizarRiesgosDatos(
      instrucciones,
      configuracion.forwarding,
      configuracion.penalizacionDatos
    );

    const resultadoSaltos = simularPredictorSaltos(
      instrucciones,
      configuracion.estadoPredictor,
      configuracion.penalizacionControl
    );

    const totalStalls = resultadoRiesgos.reduce(
      (total, riesgo) => total + riesgo.stalls,
      0
    );

    const totalFlushes = resultadoSaltos.flushes;

    const cantidad = instrucciones.length;
    const etapas = configuracion.etapas;

    const ciclosIdeales = etapas + cantidad - 1;
    const ciclosReales =
      ciclosIdeales + totalStalls + totalFlushes;

    const cpi = ciclosReales / cantidad;
    const throughput = cantidad / ciclosReales;
    const tiempoTotal =
      ciclosReales * configuracion.tiempoCiclo;

    const precision =
      resultadoSaltos.totalSaltos > 0
        ? (resultadoSaltos.aciertos /
            resultadoSaltos.totalSaltos) *
          100
        : 0;

    const resultado = {
      cantidadInstrucciones: cantidad,
      etapas,
      tiempoCiclo: configuracion.tiempoCiclo,
      unidadTiempo: configuracion.unidadTiempo,
      forwarding: configuracion.forwarding,
     ciclosIdeales: backend?.ciclosIdeales ?? ciclosIdeales,
ciclosReales: backend?.ciclosReales ?? ciclosReales,
stalls: backend?.stalls ?? totalStalls,
flushes: backend?.flushes ?? totalFlushes,
cpi: backend?.cpi ?? cpi,
throughput: backend?.throughput ?? throughput,
tiempoTotal: backend?.tiempoTotal ?? tiempoTotal,
precision: backend?.precision ?? precision,
      aciertosPredictor: resultadoSaltos.aciertos,
      fallosPredictor: resultadoSaltos.fallos,
      totalSaltos: resultadoSaltos.totalSaltos,
      instrucciones: instrucciones.map((item) => item.texto)
    };

    mostrarResultados(resultado);

    generarGantt(
      instrucciones,
      resultadoRiesgos,
      resultadoSaltos.detalles,
      configuracion,
      ciclosReales
    );

    mostrarHistorialPredictor(resultadoSaltos.detalles);

    mostrarObservaciones(
      instrucciones,
      resultadoRiesgos,
      resultadoSaltos,
      configuracion
    );

    guardarResultadoPipelineAvanzado(resultado);
  } catch (error) {
    console.error("Error en Pipeline Avanzado:", error);
    mostrarError(error.message);
  }
}


/* =========================================================
   OBTENER Y VALIDAR CONFIGURACIÓN
========================================================= */

function obtenerConfiguracion() {
  const textarea = document.getElementById(
    "instruccionesPipelineAvanzado"
  );

  const instrucciones = obtenerLineasValidas(
    textarea ? textarea.value : ""
  );

  return {
    cantidadInstrucciones: instrucciones.length,

    etapas: obtenerNumero("etapasPipeline"),

    tiempoCiclo: obtenerNumero("tiempoCiclo"),

    unidadTiempo:
      document.getElementById("unidadTiempo")?.value || "ns",

    forwarding:
      document.getElementById("forwarding")?.value === "true",

    penalizacionDatos: obtenerNumero("penalizacionDatos"),

    penalizacionControl: obtenerNumero(
      "penalizacionControl"
    ),

    estadoPredictor:
      document.getElementById("estadoPredictor")?.value || "ST",

    instrucciones
  };
}


function obtenerNumero(id) {
  const elemento = document.getElementById(id);

  if (!elemento) {
    return 0;
  }

  return Number(elemento.value);
}


function validarConfiguracion(configuracion) {
  if (configuracion.instrucciones.length === 0) {
    throw new Error(
      "Debes ingresar al menos una instrucción."
    );
  }

  if (
    !Number.isInteger(configuracion.etapas) ||
    configuracion.etapas < 3
  ) {
    throw new Error(
      "El número de etapas debe ser un entero mayor o igual que 3."
    );
  }

  if (
    !Number.isFinite(configuracion.tiempoCiclo) ||
    configuracion.tiempoCiclo <= 0
  ) {
    throw new Error(
      "El tiempo de ciclo debe ser mayor que cero."
    );
  }

  if (
    !Number.isInteger(configuracion.penalizacionDatos) ||
    configuracion.penalizacionDatos < 0
  ) {
    throw new Error(
      "La penalización por datos debe ser un entero no negativo."
    );
  }

  if (
    !Number.isInteger(configuracion.penalizacionControl) ||
    configuracion.penalizacionControl < 0
  ) {
    throw new Error(
      "La penalización por control debe ser un entero no negativo."
    );
  }
}


/* =========================================================
   PROCESAMIENTO DE TEXTO
========================================================= */

function obtenerLineasValidas(texto) {
  return texto
    .split("\n")
    .map((linea) => eliminarComentario(linea).trim())
    .filter((linea) => linea.length > 0);
}


function eliminarComentario(linea) {
  const posicionPuntoComa = linea.indexOf(";");
  const posicionNumeral = linea.indexOf("#");

  const posiciones = [
    posicionPuntoComa,
    posicionNumeral
  ].filter((posicion) => posicion >= 0);

  if (posiciones.length === 0) {
    return linea;
  }

  return linea.substring(0, Math.min(...posiciones));
}


/* =========================================================
   ANALIZADOR DE INSTRUCCIONES
========================================================= */

function analizarInstruccion(texto, indice) {
  const normalizada = texto
    .toUpperCase()
    .replace(/\s+/g, " ")
    .trim();

  const partes = normalizada.split(" ");
  const operacion = partes[0];

  const registros =
    normalizada.match(
      /\b(?:R\d+|AX|BX|CX|DX|SI|DI|SP|BP)\b/g
    ) || [];

  const tiposAritmeticos = [
    "ADD",
    "ADDI",
    "SUB",
    "SUBI",
    "MUL",
    "DIV",
    "AND",
    "OR",
    "XOR",
    "NOR",
    "SLT",
    "SLL",
    "SRL"
  ];

  const tiposCarga = ["LW", "LD", "LOAD"];
  const tiposAlmacenamiento = ["SW", "SD", "STORE"];
  const tiposMovimiento = ["MOV", "LI"];
  const tiposSaltoCondicional = ["BEQ", "BNE", "BLT", "BGT"];
  const tiposSaltoIncondicional = ["J", "JMP"];

  let destino = null;
  let fuentes = [];
  let tipo = "OTRA";

  if (tiposAritmeticos.includes(operacion)) {
    tipo = "ALU";
    destino = registros[0] || null;
    fuentes = registros.slice(1);
  } else if (tiposCarga.includes(operacion)) {
    tipo = "LOAD";
    destino = registros[0] || null;
    fuentes = registros.slice(1);
  } else if (tiposAlmacenamiento.includes(operacion)) {
    tipo = "STORE";
    fuentes = registros;
  } else if (tiposMovimiento.includes(operacion)) {
    tipo = "MOV";

    if (operacion === "LI") {
      destino = registros[0] || null;
      fuentes = [];
    } else {
      destino = registros[0] || null;
      fuentes = registros.slice(1);
    }
  } else if (tiposSaltoCondicional.includes(operacion)) {
    tipo = "BRANCH";
    fuentes = registros;
  } else if (tiposSaltoIncondicional.includes(operacion)) {
    tipo = "JUMP";
  }

  const resultadoSalto = obtenerResultadoSalto(
    normalizada,
    tipo
  );

  return {
    indice,
    numero: indice + 1,
    etiqueta: `I${indice + 1}`,
    texto: normalizada,
    operacion,
    registros,
    destino,
    fuentes,
    tipo,
    esSalto: tipo === "BRANCH" || tipo === "JUMP",
    resultadoSalto
  };
}


function obtenerResultadoSalto(texto, tipo) {
  if (tipo === "JUMP") {
    return true;
  }

  if (tipo !== "BRANCH") {
    return null;
  }

  const tokens = texto.split(/\s+/);
  const ultimoToken = tokens[tokens.length - 1];

  if (
    ultimoToken === "T" ||
    ultimoToken === "TAKEN" ||
    ultimoToken === "TOMADO"
  ) {
    return true;
  }

  if (
    ultimoToken === "N" ||
    ultimoToken === "NT" ||
    ultimoToken === "NOT-TAKEN" ||
    ultimoToken === "NO-TOMADO"
  ) {
    return false;
  }

  /*
   * Cuando no se indica T o N, se considera no tomado.
   */
  return false;
}


/* =========================================================
   DETECCIÓN DE HAZARDS RAW
========================================================= */

function analizarRiesgosDatos(
  instrucciones,
  forwarding,
  penalizacionDatos
) {
  const ultimaEscritura = new Map();
  const resultados = [];

  instrucciones.forEach((instruccion, indiceActual) => {
    let stalls = 0;
    const dependencias = [];

    instruccion.fuentes.forEach((registro) => {
      if (!ultimaEscritura.has(registro)) {
        return;
      }

      const productor = ultimaEscritura.get(registro);
      const distancia = indiceActual - productor.indice;

      let penalizacion = 0;

      if (forwarding) {
        /*
         * Con forwarding, una dependencia ALU-ALU no genera
         * stall. Una dependencia inmediata desde LOAD genera
         * un stall por el riesgo load-use.
         */
        if (
          productor.tipo === "LOAD" &&
          distancia === 1
        ) {
          penalizacion = Math.min(
            1,
            penalizacionDatos
          );
        }
      } else {
        /*
         * Sin forwarding, se aplica la penalización configurada
         * cuando el productor todavía está próximo.
         */
        if (distancia <= 2) {
          penalizacion = penalizacionDatos;
        }
      }

      if (penalizacion > 0) {
        stalls = Math.max(stalls, penalizacion);

        dependencias.push({
          registro,
          productor: productor.etiqueta,
          consumidor: instruccion.etiqueta,
          distancia,
          penalizacion,
          tipoProductor: productor.tipo
        });
      }
    });

    resultados.push({
      instruccion: instruccion.etiqueta,
      stalls,
      dependencias
    });

    if (instruccion.destino) {
      ultimaEscritura.set(instruccion.destino, {
        indice: indiceActual,
        etiqueta: instruccion.etiqueta,
        tipo: instruccion.tipo,
        operacion: instruccion.operacion
      });
    }
  });

  return resultados;
}


/* =========================================================
   PREDICTOR DINÁMICO DE 2 BITS
========================================================= */

function simularPredictorSaltos(
  instrucciones,
  estadoInicial,
  penalizacionControl
) {
  let estado = convertirEstadoPredictor(estadoInicial);

  let aciertos = 0;
  let fallos = 0;
  let flushes = 0;

  const detalles = [];

  instrucciones.forEach((instruccion) => {
    if (!instruccion.esSalto) {
      return;
    }

    const estadoAntes = estado;
    const prediccionTomado = estadoAntes >= 2;
    const resultadoTomado = instruccion.resultadoSalto;

    const acierto =
      prediccionTomado === resultadoTomado;

    if (acierto) {
      aciertos++;
    } else {
      fallos++;
      flushes += penalizacionControl;
    }

    estado = actualizarEstadoPredictor(
      estadoAntes,
      resultadoTomado
    );

    detalles.push({
      indice: instruccion.indice,
      instruccion: instruccion.etiqueta,
      codigo: instruccion.texto,
      estadoAntes,
      estadoAntesTexto:
        obtenerNombreEstadoPredictor(estadoAntes),
      prediccionTomado,
      prediccionTexto: prediccionTomado
        ? "TOMADO"
        : "NO TOMADO",
      resultadoTomado,
      resultadoTexto: resultadoTomado
        ? "TOMADO"
        : "NO TOMADO",
      acierto,
      evaluacion: acierto ? "ACIERTO" : "FALLO",
      estadoDespues: estado,
      estadoDespuesTexto:
        obtenerNombreEstadoPredictor(estado),
      ciclosFlush: acierto ? 0 : penalizacionControl
    });
  });

  return {
    aciertos,
    fallos,
    flushes,
    totalSaltos: aciertos + fallos,
    estadoFinal: estado,
    estadoFinalTexto:
      obtenerNombreEstadoPredictor(estado),
    detalles
  };
}


function convertirEstadoPredictor(estado) {
  const estados = {
    SNT: 0,
    WNT: 1,
    WT: 2,
    ST: 3
  };

  return estados[estado] ?? 3;
}


function actualizarEstadoPredictor(
  estadoActual,
  resultadoTomado
) {
  if (resultadoTomado) {
    return Math.min(3, estadoActual + 1);
  }

  return Math.max(0, estadoActual - 1);
}


function obtenerNombreEstadoPredictor(estado) {
  const nombres = [
    "Strong Not Taken",
    "Weak Not Taken",
    "Weak Taken",
    "Strong Taken"
  ];

  return nombres[estado] || "Estado desconocido";
}


/* =========================================================
   MOSTRAR RESULTADOS
========================================================= */

function mostrarResultados(resultado) {
  asignarTexto(
    "statCiclosIdeales",
    resultado.ciclosIdeales
  );

  asignarTexto(
    "statCiclosReales",
    resultado.ciclosReales
  );

  asignarTexto(
    "statCPI",
    resultado.cpi.toFixed(2)
  );

  asignarTexto(
    "statThroughput",
    resultado.throughput.toFixed(4)
  );

  asignarTexto(
    "resStalls",
    resultado.stalls
  );

  asignarTexto(
    "resFlushes",
    resultado.flushes
  );

  asignarTexto(
    "resTiempoTotal",
    `${formatearNumero(resultado.tiempoTotal)} ${resultado.unidadTiempo}`
  );

  asignarTexto(
    "resPrecision",
    `${resultado.precision.toFixed(2)}%`
  );
}


function asignarTexto(id, valor) {
  const elemento = document.getElementById(id);

  if (elemento) {
    elemento.textContent = valor;
  }
}


function formatearNumero(valor) {
  if (Number.isInteger(valor)) {
    return valor.toString();
  }

  return valor.toFixed(2);
}


/* =========================================================
   DIAGRAMA DE TIEMPOS / GANTT
========================================================= */

function generarGantt(
  instrucciones,
  riesgos,
  detallesSaltos,
  configuracion,
  ciclosReales
) {
  const simulacion = simularPipelineCicloPorCiclo(
    instrucciones,
    riesgos,
    detallesSaltos,
    configuracion
  );

  renderizarGanttV2(simulacion);
}
/* =========================================================
   GANTT V2 - SIMULACIÓN CICLO POR CICLO
========================================================= */

function simularPipelineCicloPorCiclo(
  instrucciones,
  riesgos,
  detallesSaltos,
  configuracion
) {
  const etapas = generarNombresEtapas(configuracion.etapas);
  const gantt = instrucciones.map((instruccion) => ({
    instruccion,
    ciclos: []
  }));

  let cicloGlobal = 1;
  let retrasoAcumulado = 0;

  instrucciones.forEach((instruccion, indice) => {
    let cicloActual = indice + 1 + retrasoAcumulado;

    const riesgo = riesgos[indice] || { stalls: 0 };
    const salto = detallesSaltos.find(
      (item) => item.indice === indice
    );

    agregarCeldaGanttV2(gantt, indice, cicloActual, etapas[0]);
    cicloActual++;

    agregarCeldaGanttV2(gantt, indice, cicloActual, etapas[1]);
    cicloActual++;

    for (let i = 0; i < riesgo.stalls; i++) {
      agregarCeldaGanttV2(gantt, indice, cicloActual, "STALL");
      cicloActual++;
      retrasoAcumulado++;
    }

    if (instruccion.esSalto) {
      agregarCeldaGanttV2(gantt, indice, cicloActual, "EX");
      cicloActual++;

      if (salto && !salto.acierto) {
        for (let i = 0; i < salto.ciclosFlush; i++) {
          agregarCeldaGanttV2(gantt, indice, cicloActual, "FLUSH");
          cicloActual++;
          retrasoAcumulado++;
        }
      }
    } else {
      for (let e = 2; e < etapas.length; e++) {
        agregarCeldaGanttV2(gantt, indice, cicloActual, etapas[e]);
        cicloActual++;
      }
    }

    cicloGlobal = Math.max(cicloGlobal, cicloActual - 1);
  });

  return {
    gantt,
    totalCiclos: cicloGlobal,
    etapas
  };
}

function agregarCeldaGanttV2(gantt, indice, ciclo, etapa) {
  gantt[indice].ciclos.push({
    ciclo,
    etapa
  });
}

function renderizarGanttV2(simulacion) {
  const encabezado = document.getElementById("ganttHead");
  const cuerpo = document.getElementById("ganttBody");

  if (!encabezado || !cuerpo) return;

  encabezado.innerHTML = "";
  cuerpo.innerHTML = "";

  const totalCiclos = Math.min(simulacion.totalCiclos, 60);

  const filaHead = document.createElement("tr");

  const thInicial = document.createElement("th");
  thInicial.textContent = "Instrucción";
  filaHead.appendChild(thInicial);

  for (let ciclo = 1; ciclo <= totalCiclos; ciclo++) {
    const th = document.createElement("th");
    th.textContent = `C${ciclo}`;
    filaHead.appendChild(th);
  }

  encabezado.appendChild(filaHead);

  simulacion.gantt.forEach((filaGantt) => {
    const fila = document.createElement("tr");

    const tdNombre = document.createElement("td");
    tdNombre.textContent =
      `${filaGantt.instruccion.etiqueta} (${filaGantt.instruccion.operacion})`;
    tdNombre.title = filaGantt.instruccion.texto;
    tdNombre.className = "gantt-instruccion";

    fila.appendChild(tdNombre);

    for (let ciclo = 1; ciclo <= totalCiclos; ciclo++) {
      const td = document.createElement("td");

      const celda = filaGantt.ciclos.find(
        (item) => item.ciclo === ciclo
      );

      if (celda) {
        td.textContent = celda.etapa;
        td.classList.add(obtenerClaseEtapa(celda.etapa));
      } else {
        td.textContent = "—";
        td.classList.add("etapa-vacia");
      }

      fila.appendChild(td);
    }

    cuerpo.appendChild(fila);
  });

  if (simulacion.totalCiclos > 60) {
    const fila = document.createElement("tr");
    const td = document.createElement("td");

    td.colSpan = totalCiclos + 1;
    td.textContent =
      `Se muestran los primeros 60 ciclos de ${simulacion.totalCiclos}.`;

    fila.appendChild(td);
    cuerpo.appendChild(fila);
  }
}
 
function generarNombresEtapas(cantidadEtapas) {
  if (cantidadEtapas === 5) {
    return ["IF", "ID", "EX", "MEM", "WB"];
  }

  if (cantidadEtapas === 4) {
    return ["IF", "ID", "EX", "WB"];
  }

  if (cantidadEtapas === 3) {
    return ["IF", "EX", "WB"];
  }

  const etapas = ["IF", "ID"];
  const cantidadEjecucion = cantidadEtapas - 4;

  for (
    let numero = 1;
    numero <= cantidadEjecucion;
    numero++
  ) {
    etapas.push(`E${numero}`);
  }

  etapas.push("MEM");
  etapas.push("WB");

  return etapas;
}




function obtenerClaseEtapa(etapa) {
  if (etapa === "IF") {
    return "etapa-if";
  }

  if (etapa === "ID") {
    return "etapa-id";
  }

  if (
    etapa === "EX" ||
    etapa.startsWith("E")
  ) {
    return "etapa-ex";
  }

  if (etapa === "MEM") {
    return "etapa-mem";
  }

  if (etapa === "WB") {
    return "etapa-wb";
  }

  if (etapa === "STALL") {
    return "etapa-stall";
  }

  if (etapa === "FLUSH") {
    return "etapa-flush";
  }

  return "";
}


/* =========================================================
   TABLA DEL PREDICTOR
========================================================= */

function mostrarHistorialPredictor(detalles) {
  const tabla = document.getElementById("tablaPredictor");

  if (!tabla) {
    return;
  }

  tabla.innerHTML = "";

  if (detalles.length === 0) {
    tabla.innerHTML = `
      <tr>
        <td colspan="5">
          El programa no contiene instrucciones de salto.
        </td>
      </tr>
    `;

    return;
  }

  detalles.forEach((detalle) => {
    const fila = document.createElement("tr");

    agregarCelda(
      fila,
      detalle.instruccion,
      detalle.codigo
    );

    agregarCelda(
      fila,
      detalle.estadoAntesTexto
    );

    agregarCelda(
      fila,
      detalle.prediccionTexto
    );

    agregarCelda(
      fila,
      detalle.resultadoTexto
    );

    const celdaEvaluacion = document.createElement("td");

    celdaEvaluacion.textContent = detalle.evaluacion;
    celdaEvaluacion.className = detalle.acierto
      ? "predictor-acierto"
      : "predictor-fallo";

    fila.appendChild(celdaEvaluacion);
    tabla.appendChild(fila);
  });
}


function agregarCelda(fila, texto, titulo = "") {
  const celda = document.createElement("td");

  celda.textContent = texto;

  if (titulo) {
    celda.title = titulo;
  }

  fila.appendChild(celda);
}


/* =========================================================
   OBSERVACIONES
========================================================= */

function mostrarObservaciones(
  instrucciones,
  riesgos,
  saltos,
  configuracion
) {
  const contenedor = document.getElementById(
    "observacionesPipelineAvanzado"
  );

  if (!contenedor) {
    return;
  }

  contenedor.innerHTML = "";

  const lista = document.createElement("ul");
  lista.className = "observation-list";

  let cantidadObservaciones = 0;

  riesgos.forEach((riesgo, indice) => {
    if (riesgo.stalls <= 0) {
      return;
    }

    cantidadObservaciones++;

    const dependencias = riesgo.dependencias
      .map(
        (dependencia) =>
          `${dependencia.productor} → ${dependencia.consumidor} por ${dependencia.registro}`
      )
      .join(", ");

    agregarObservacion(
      lista,
      `Riesgo RAW en ${instrucciones[indice].etiqueta}: ` +
        `${dependencias}. Se insertaron ${riesgo.stalls} stall(s).`
    );
  });

  saltos.detalles.forEach((salto) => {
    cantidadObservaciones++;

    if (salto.acierto) {
      agregarObservacion(
        lista,
        `${salto.instruccion}: el predictor acertó ` +
          `(${salto.prediccionTexto}).`
      );
    } else {
      agregarObservacion(
        lista,
        `${salto.instruccion}: predicción incorrecta. ` +
          `Se aplicaron ${salto.ciclosFlush} ciclo(s) de flush.`
      );
    }
  });

  if (configuracion.forwarding) {
    cantidadObservaciones++;

    agregarObservacion(
      lista,
      "Forwarding activado: las dependencias ALU-ALU se resuelven sin stalls."
    );
  } else {
    cantidadObservaciones++;

    agregarObservacion(
      lista,
      "Forwarding desactivado: las dependencias RAW cercanas generan paradas."
    );
  }

  if (cantidadObservaciones === 0) {
    agregarObservacion(
      lista,
      "La ejecución no presentó riesgos ni penalizaciones."
    );
  }

  contenedor.appendChild(lista);
}


function agregarObservacion(lista, texto) {
  const elemento = document.createElement("li");
  elemento.textContent = texto;
  lista.appendChild(elemento);
}


/* =========================================================
   LIMPIAR Y REINICIAR
========================================================= */

function limpiarPipelineAvanzado() {
  asignarTexto("statCiclosIdeales", "0");
  asignarTexto("statCiclosReales", "0");
  asignarTexto("statCPI", "0.00");
  asignarTexto("statThroughput", "0.0000");

  asignarTexto("resStalls", "0");
  asignarTexto("resFlushes", "0");
  asignarTexto("resTiempoTotal", "0 ns");
  asignarTexto("resPrecision", "0%");

  const ganttHead = document.getElementById("ganttHead");
  const ganttBody = document.getElementById("ganttBody");
  const predictor = document.getElementById("tablaPredictor");
  const observaciones = document.getElementById(
    "observacionesPipelineAvanzado"
  );

  if (ganttHead) {
    ganttHead.innerHTML = "";
  }

  if (ganttBody) {
    ganttBody.innerHTML = `
      <tr>
        <td colspan="10">
          Ejecuta la simulación para generar la carta de tiempos.
        </td>
      </tr>
    `;
  }

  if (predictor) {
    predictor.innerHTML = `
      <tr>
        <td colspan="5">Sin datos.</td>
      </tr>
    `;
  }

  if (observaciones) {
    observaciones.textContent =
      "Ejecuta la simulación para ver riesgos, stalls, flushes y predicción de saltos.";
  }
}


function reiniciarPipelineAvanzado() {
  const valores = CONFIG_PIPELINE_AVANZADO;

  asignarValor(
    "cantidadInstrucciones",
    valores.cantidadInstrucciones
  );

  asignarValor(
    "etapasPipeline",
    valores.etapas
  );

  asignarValor(
    "tiempoCiclo",
    valores.tiempoCiclo
  );

  asignarValor(
    "unidadTiempo",
    valores.unidadTiempo
  );

  asignarValor(
    "forwarding",
    String(valores.forwarding)
  );

  asignarValor(
    "penalizacionDatos",
    valores.penalizacionDatos
  );

  asignarValor(
    "penalizacionControl",
    valores.penalizacionControl
  );

  asignarValor(
    "estadoPredictor",
    valores.estadoPredictor
  );

  asignarValor(
    "instruccionesPipelineAvanzado",
    valores.instrucciones
  );

  localStorage.removeItem("resultadoPipelineAvanzado");

  limpiarPipelineAvanzado();
  actualizarCantidadInstrucciones();
}


function asignarValor(id, valor) {
  const elemento = document.getElementById(id);

  if (elemento) {
    elemento.value = valor;
  }
}


/* =========================================================
   LOCAL STORAGE
========================================================= */

function guardarResultadoPipelineAvanzado(resultado) {
  try {
    localStorage.setItem(
      "resultadoPipelineAvanzado",
      JSON.stringify(resultado)
    );
  } catch (error) {
    console.warn(
      "No se pudo guardar resultadoPipelineAvanzado:",
      error
    );
  }
}


/* =========================================================
   MENSAJES DE ERROR
========================================================= */

function mostrarError(mensaje) {
  const contenedor = document.getElementById(
    "observacionesPipelineAvanzado"
  );

  if (contenedor) {
    contenedor.innerHTML = "";

    const elemento = document.createElement("p");
    elemento.className = "mensaje-error";
    elemento.textContent = mensaje;

    contenedor.appendChild(elemento);
  } else {
    alert(mensaje);
  }
}


/* =========================================================
   EXPOSICIÓN GLOBAL PARA LOS BOTONES DEL HTML
========================================================= */

window.initPipelineAvanzado = initPipelineAvanzado;
window.ejecutarPipelineAvanzado =
  ejecutarPipelineAvanzado;
window.limpiarPipelineAvanzado =
  limpiarPipelineAvanzado;
window.reiniciarPipelineAvanzado =
  reiniciarPipelineAvanzado;


/*
 * Respaldo por si app.js todavía no llama al inicializador.
 */
document.addEventListener("DOMContentLoaded", () => {
  initPipelineAvanzado();
});
let simulacionPasoPipeline = null;
let cicloPasoPipeline = 0;

function prepararSimulacionPasoAPaso() {
  const configuracion = obtenerConfiguracion();
  validarConfiguracion(configuracion);

  const instrucciones = configuracion.instrucciones.map(
    (texto, indice) => analizarInstruccion(texto, indice)
  );

  const riesgos = analizarRiesgosDatos(
    instrucciones,
    configuracion.forwarding,
    configuracion.penalizacionDatos
  );

  const saltos = simularPredictorSaltos(
    instrucciones,
    configuracion.estadoPredictor,
    configuracion.penalizacionControl
  );

  simulacionPasoPipeline = simularPipelineCicloPorCiclo(
    instrucciones,
    riesgos,
    saltos.detalles,
    configuracion
  );

  cicloPasoPipeline = 0;

  asignarTexto("cicloActualPipeline", "0");
  asignarTexto("estadoSimulacionPipeline", "Preparado");

  const vista = document.getElementById("vistaCicloPipeline");
  if (vista) {
    vista.textContent = "Simulación preparada. Presiona Siguiente ciclo.";
  }
}

function siguienteCicloPipeline() {
  if (!simulacionPasoPipeline) {
    prepararSimulacionPasoAPaso();
  }

  if (cicloPasoPipeline >= simulacionPasoPipeline.totalCiclos) {
    asignarTexto("estadoSimulacionPipeline", "Finalizado");
    return;
  }

  cicloPasoPipeline++;

  asignarTexto("cicloActualPipeline", cicloPasoPipeline);
  asignarTexto("estadoSimulacionPipeline", "Ejecutando");

  mostrarCicloActualPipeline(cicloPasoPipeline);
}

function mostrarCicloActualPipeline(ciclo) {
  const vista = document.getElementById("vistaCicloPipeline");
  if (!vista || !simulacionPasoPipeline) return;

  const actividades = [];

  simulacionPasoPipeline.gantt.forEach((fila) => {
    const celda = fila.ciclos.find((item) => item.ciclo === ciclo);

    if (celda) {
      actividades.push(
        `${fila.instruccion.etiqueta} (${fila.instruccion.operacion}) → ${celda.etapa}`
      );
    }
  });

  if (actividades.length === 0) {
    vista.innerHTML = `<p>No hay actividad en el ciclo ${ciclo}.</p>`;
    return;
  }

  vista.innerHTML = `
    <h3>Ciclo ${ciclo}</h3>
    <ul class="observation-list">
      ${actividades.map((item) => `<li>${item}</li>`).join("")}
    </ul>
  `;

  resaltarColumnaGantt(ciclo);
}

function resaltarColumnaGantt(ciclo) {
  const tabla = document.getElementById("tablaGantt");
  if (!tabla) return;

  tabla.querySelectorAll("td, th").forEach((celda) => {
    celda.classList.remove("ciclo-activo");
  });

  const indiceColumna = ciclo + 1;

  tabla.querySelectorAll("tr").forEach((fila) => {
    const celda = fila.children[indiceColumna - 1];
    if (celda) {
      celda.classList.add("ciclo-activo");
    }
  });
}

function reiniciarSimulacionPasoAPaso() {
  simulacionPasoPipeline = null;
  cicloPasoPipeline = 0;

  asignarTexto("cicloActualPipeline", "0");
  asignarTexto("estadoSimulacionPipeline", "Detenido");

  const vista = document.getElementById("vistaCicloPipeline");
  if (vista) {
    vista.textContent = "Prepara la simulación para avanzar ciclo por ciclo.";
  }

  const tabla = document.getElementById("tablaGantt");
  if (tabla) {
    tabla.querySelectorAll("td, th").forEach((celda) => {
      celda.classList.remove("ciclo-activo");
    });
  }
}

window.prepararSimulacionPasoAPaso = prepararSimulacionPasoAPaso;
window.siguienteCicloPipeline = siguienteCicloPipeline;
window.reiniciarSimulacionPasoAPaso = reiniciarSimulacionPasoAPaso;