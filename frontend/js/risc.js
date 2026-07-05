// ===============================
// MÓDULO RISC VISUAL
// ===============================

const registrosRisc = {
  R0: 0, R1: 0, R2: 0, R3: 0,
  R4: 0, R5: 0, R6: 0, R7: 0,
  R8: 0, R9: 0, R10: 0, R11: 0,
  R12: 0, R13: 0, R14: 0, R15: 0
};

const memoriaRisc = {
  "0x100": { variable: "A", valor: 12 },
  "0x104": { variable: "B", valor: 8 },
  "0x108": { variable: "C", valor: 15 },
  "0x10C": { variable: "D", valor: 10 },
  "0x110": { variable: "Resultado", valor: "Pendiente" }
};

const instruccionesRisc = [
  "LI R0, 0x100",
  "LW R1, 0(R0)",
  "LW R2, 4(R0)",
  "LW R3, 8(R0)",
  "LW R4, 12(R0)",
  "ADD R5, R1, R2",
  "SUB R6, R3, R4",
  "MUL R7, R5, R6",
  "SW R7, 16(R0)"
];

function inicializarRisc() {

    cargarModuloRisc();

    document
        .getElementById("btnEjecutarRisc")
        ?.addEventListener("click", ejecutarRisc);

    document
        .getElementById("btnReiniciarRisc")
        ?.addEventListener("click", reiniciarRisc);

}

function cargarModuloRisc() {
  pintarRegistrosRisc();
  pintarMemoriaRisc();
}

function obtenerDatosEntradaRisc() {
  return {
    A: Number(document.getElementById("inputA_Risc")?.value || 12),
    B: Number(document.getElementById("inputB_Risc")?.value || 8),
    C: Number(document.getElementById("inputC_Risc")?.value || 15),
    D: Number(document.getElementById("inputD_Risc")?.value || 10)
  };
}

function pintarRegistrosRisc() {
  const tabla = document.getElementById("tablaRegistrosRisc");
  if (!tabla) return;

  tabla.innerHTML = "";

  Object.entries(registrosRisc).forEach(([registro, valor]) => {
    tabla.innerHTML += `
      <tr>
        <td>${registro}</td>
        <td>${valor}</td>
      </tr>
    `;
  });
}

function pintarMemoriaRisc() {
  const tabla = document.getElementById("tablaMemoriaRisc");
  if (!tabla) return;

  tabla.innerHTML = "";

  Object.entries(memoriaRisc).forEach(([direccion, dato]) => {
    tabla.innerHTML += `
      <tr>
        <td>${direccion}</td>
        <td>${dato.variable}</td>
        <td>${dato.valor}</td>
      </tr>
    `;
  });
}

function agregarHistorialRisc(paso, instruccion, accion, resultado) {
  const historial = document.getElementById("historialRisc");
  if (!historial) return;

  historial.innerHTML += `
    <tr>
      <td>${paso}</td>
      <td>${instruccion}</td>
      <td>${accion}</td>
      <td>${resultado}</td>
    </tr>
  `;
}

function actualizarALU(operacion, a, b, resultado) {
  document.getElementById("aluOperacion").textContent = operacion;
  document.getElementById("aluA").textContent = a;
  document.getElementById("aluB").textContent = b;
  document.getElementById("aluResultado").textContent = resultado;
}

function marcarLineaRisc(indice) {

  const lineas = document.querySelectorAll("#riscCode div");

  lineas.forEach(linea => {
    linea.classList.remove("active-line");
  });

  if (indice >= 0 && indice < lineas.length) {
    lineas[indice].classList.add("active-line");
  }

}

async function ejecutarRisc() {
  const datos = obtenerDatosEntradaRisc();

  limpiarRisc();

  const respuesta = await postData("/api/risc", datos);
  if (respuesta) {
  console.log("Respuesta backend RISC:", respuesta);
}

  let paso = 0;

  const ejecucion = [
    () => {
      registrosRisc.R0 = "0x100";
      agregarHistorialRisc(++paso, instruccionesRisc[0], "Carga inmediata", "R0 = 0x100");
    },
    () => {
      registrosRisc.R1 = memoriaRisc["0x100"].valor;
      agregarHistorialRisc(++paso, instruccionesRisc[1], "Load", `R1 = ${registrosRisc.R1}`);
    },
    () => {
      registrosRisc.R2 = memoriaRisc["0x104"].valor;
      agregarHistorialRisc(++paso, instruccionesRisc[2], "Load", `R2 = ${registrosRisc.R2}`);
    },
    () => {
      registrosRisc.R3 = memoriaRisc["0x108"].valor;
      agregarHistorialRisc(++paso, instruccionesRisc[3], "Load", `R3 = ${registrosRisc.R3}`);
    },
    () => {
      registrosRisc.R4 = memoriaRisc["0x10C"].valor;
      agregarHistorialRisc(++paso, instruccionesRisc[4], "Load", `R4 = ${registrosRisc.R4}`);
    },
    () => {
      registrosRisc.R5 = registrosRisc.R1 + registrosRisc.R2;
      actualizarALU("ADD", registrosRisc.R1, registrosRisc.R2, registrosRisc.R5);
      agregarHistorialRisc(++paso, instruccionesRisc[5], "ALU", `R5 = ${registrosRisc.R5}`);
    },
    () => {
      registrosRisc.R6 = registrosRisc.R3 - registrosRisc.R4;
      actualizarALU("SUB", registrosRisc.R3, registrosRisc.R4, registrosRisc.R6);
      agregarHistorialRisc(++paso, instruccionesRisc[6], "ALU", `R6 = ${registrosRisc.R6}`);
    },
    () => {
      registrosRisc.R7 = registrosRisc.R5 * registrosRisc.R6;
      actualizarALU("MUL", registrosRisc.R5, registrosRisc.R6, registrosRisc.R7);
      agregarHistorialRisc(++paso, instruccionesRisc[7], "ALU", `R7 = ${registrosRisc.R7}`);
    },
    () => {
      memoriaRisc["0x110"].valor = registrosRisc.R7;
      document.getElementById("resultadoRisc").textContent = registrosRisc.R7;
      agregarHistorialRisc(++paso, instruccionesRisc[8], "Store", `Memoria[0x110] = ${registrosRisc.R7}`);
      localStorage.setItem(
    "resultadoRisc",
    JSON.stringify({
        instrucciones: 9,
        memoria: 5,
        complejidad: 35,
        pipeline: 95,
        resultado: registrosRisc.R7
    }));
    agregarHistorialRisc(
    ++paso,
    instruccionesRisc[8],
    "Store",
    `Memoria[0x110] = ${registrosRisc.R7}`
    );
    }
  ];

  ejecucion.forEach((accion, index) => {
    setTimeout(() => {
      marcarLineaRisc(index);
      accion();
      pintarRegistrosRisc();
      pintarMemoriaRisc();
    }, index * 700);
  });
}

function limpiarRisc() {

  const datos = obtenerDatosEntradaRisc();

  Object.keys(registrosRisc).forEach(registro => {
    registrosRisc[registro] = 0;
  });

  memoriaRisc["0x100"].valor = datos.A;
  memoriaRisc["0x104"].valor = datos.B;
  memoriaRisc["0x108"].valor = datos.C;
  memoriaRisc["0x10C"].valor = datos.D;
  memoriaRisc["0x110"].valor = "Pendiente";

  document.getElementById("historialRisc").innerHTML = "";
  document.getElementById("resultadoRisc").textContent = "Pendiente";

  actualizarALU("---", "---", "---", "---");
  marcarLineaRisc(-1);

  pintarRegistrosRisc();
  pintarMemoriaRisc();

}

function reiniciarRisc() {

  document.getElementById("inputA_Risc").value = 0;
  document.getElementById("inputB_Risc").value = 0;
  document.getElementById("inputC_Risc").value = 0;
  document.getElementById("inputD_Risc").value = 0;

  limpiarRisc();

}