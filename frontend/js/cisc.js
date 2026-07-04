// ===============================
// MÓDULO CISC VISUAL
// ===============================

const registrosCisc = {
  AX: 0,
  BX: 0,
  CX: 0,
  DX: 0
};

const memoriaCisc = {
  "0x100": { variable: "A", valor: 12 },
  "0x104": { variable: "B", valor: 8 },
  "0x108": { variable: "C", valor: 15 },
  "0x10C": { variable: "D", valor: 10 },
  "0x110": { variable: "Resultado", valor: "Pendiente" }
};

const instruccionesCisc = [
  "MOV AX, [0x100]",
  "ADD AX, [0x104]",
  "MOV BX, [0x108]",
  "SUB BX, [0x10C]",
  "MUL BX",
  "MOV [0x110], AX"
];

function inicializarCisc() {
  cargarModuloCisc();

  document
    .getElementById("btnEjecutarCisc")
    ?.addEventListener("click", ejecutarCisc);

  document
    .getElementById("btnReiniciarCisc")
    ?.addEventListener("click", reiniciarCisc);
}

function cargarModuloCisc() {
  pintarRegistrosCisc();
  pintarMemoriaCisc();
}

function obtenerDatosEntradaCisc() {
  return {
    A: Number(document.getElementById("inputA_Cisc")?.value || 12),
    B: Number(document.getElementById("inputB_Cisc")?.value || 8),
    C: Number(document.getElementById("inputC_Cisc")?.value || 15),
    D: Number(document.getElementById("inputD_Cisc")?.value || 10)
  };
}

function pintarRegistrosCisc() {
  const tabla = document.getElementById("tablaRegistrosCisc");
  if (!tabla) return;

  tabla.innerHTML = "";

  Object.entries(registrosCisc).forEach(([registro, valor]) => {
    tabla.innerHTML += `
      <tr>
        <td>${registro}</td>
        <td>${valor}</td>
      </tr>
    `;
  });
}

function pintarMemoriaCisc() {
  const tabla = document.getElementById("tablaMemoriaCisc");
  if (!tabla) return;

  tabla.innerHTML = "";

  Object.entries(memoriaCisc).forEach(([direccion, dato]) => {
    tabla.innerHTML += `
      <tr>
        <td>${direccion}</td>
        <td>${dato.variable}</td>
        <td>${dato.valor}</td>
      </tr>
    `;
  });
}

function agregarHistorialCisc(paso, instruccion, accion, resultado) {
  const historial = document.getElementById("historialCisc");
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

function actualizarUnidadCisc(operacion, a, b, resultado) {
  document.getElementById("ciscOperacion").textContent = operacion;
  document.getElementById("ciscA").textContent = a;
  document.getElementById("ciscB").textContent = b;
  document.getElementById("ciscResultadoAlu").textContent = resultado;
}

function marcarLineaCisc(indice) {
  const lineas = document.querySelectorAll("#ciscCode div");

  lineas.forEach(linea => {
    linea.classList.remove("active-line");
  });

  if (indice >= 0 && indice < lineas.length) {
    lineas[indice].classList.add("active-line");
  }
}

async function ejecutarCisc() {

    const datos = obtenerDatosEntradaCisc();

    limpiarCisc();

    const respuesta = await postData("/cisc/simular", datos);
  let paso = 0;

  const ejecucion = [
    () => {
      registrosCisc.AX = memoriaCisc["0x100"].valor;
      agregarHistorialCisc(++paso, instruccionesCisc[0], "Carga directa memoria-registro", `AX = ${registrosCisc.AX}`);
    },
    () => {
      const antes = registrosCisc.AX;
      registrosCisc.AX += memoriaCisc["0x104"].valor;
      actualizarUnidadCisc("ADD", antes, memoriaCisc["0x104"].valor, registrosCisc.AX);
      agregarHistorialCisc(++paso, instruccionesCisc[1], "Suma directa con memoria", `AX = ${registrosCisc.AX}`);
    },
    () => {
      registrosCisc.BX = memoriaCisc["0x108"].valor;
      agregarHistorialCisc(++paso, instruccionesCisc[2], "Carga directa memoria-registro", `BX = ${registrosCisc.BX}`);
    },
    () => {
      const antes = registrosCisc.BX;
      registrosCisc.BX -= memoriaCisc["0x10C"].valor;
      actualizarUnidadCisc("SUB", antes, memoriaCisc["0x10C"].valor, registrosCisc.BX);
      agregarHistorialCisc(++paso, instruccionesCisc[3], "Resta directa con memoria", `BX = ${registrosCisc.BX}`);
    },
    () => {
      const antes = registrosCisc.AX;
      registrosCisc.AX *= registrosCisc.BX;
      actualizarUnidadCisc("MUL", antes, registrosCisc.BX, registrosCisc.AX);
      agregarHistorialCisc(++paso, instruccionesCisc[4], "Multiplicación implícita", `AX = ${registrosCisc.AX}`);
    },
    () => {
      memoriaCisc["0x110"].valor = registrosCisc.AX;
      document.getElementById("resultadoCisc").textContent = registrosCisc.AX;

    localStorage.setItem("resultadoCisc", JSON.stringify({
    arquitectura: "CISC",
    instrucciones: 6,
    memoria: 4,
    alu: 3,
    registros: 2,
    complejidad: 90,
    pipeline: 65,
    resultado: registrosCisc.AX
  }));


      agregarHistorialCisc(++paso, instruccionesCisc[5], "Store directo a memoria", `Memoria[0x110] = ${registrosCisc.AX}`);
    }
  ];

  ejecucion.forEach((accion, index) => {
    setTimeout(() => {
      marcarLineaCisc(index);
      accion();
      pintarRegistrosCisc();
      pintarMemoriaCisc();
    }, index * 700);
  });
}

function limpiarCisc() {

  const datos = obtenerDatosEntradaCisc();

  Object.keys(registrosCisc).forEach(registro => {
    registrosCisc[registro] = 0;
  });

  memoriaCisc["0x100"].valor = datos.A;
  memoriaCisc["0x104"].valor = datos.B;
  memoriaCisc["0x108"].valor = datos.C;
  memoriaCisc["0x10C"].valor = datos.D;
  memoriaCisc["0x110"].valor = "Pendiente";

  document.getElementById("historialCisc").innerHTML = "";
  document.getElementById("resultadoCisc").textContent = "Pendiente";

  actualizarUnidadCisc("---", "---", "---", "---");
  marcarLineaCisc(-1);

  pintarRegistrosCisc();
  pintarMemoriaCisc();

}

function reiniciarCisc() {

  document.getElementById("inputA_Cisc").value = 0;
  document.getElementById("inputB_Cisc").value = 0;
  document.getElementById("inputC_Cisc").value = 0;
  document.getElementById("inputD_Cisc").value = 0;

  limpiarCisc();

}