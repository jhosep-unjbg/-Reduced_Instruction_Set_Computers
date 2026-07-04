console.log("Frontend del Simulador cargado.");

function calcularPipeline() {
  const k = Number(document.getElementById("k").value);
  const n = Number(document.getElementById("n").value);
  const tau = Number(document.getElementById("tau").value);

  if (k <= 0 || n <= 0 || tau <= 0) {
    alert("Ingrese valores mayores que cero.");
    return;
  }

  const ciclos = k + (n - 1);
  const tiempo = ciclos * tau;
  const speedup = (n * k) / ciclos;
  const eficiencia = (speedup / k) * 100;

  document.getElementById("ciclos").textContent = ciclos + " ciclos";
  document.getElementById("tiempo").textContent = tiempo.toFixed(2) + " ns";
  document.getElementById("speedup").textContent = speedup.toFixed(2) + "x";
  document.getElementById("eficiencia").textContent = eficiencia.toFixed(2) + "%";

  document.getElementById("statCiclos").textContent = ciclos;
  document.getElementById("statTiempo").textContent = tiempo.toFixed(2) + " ns";
  document.getElementById("statSpeedup").textContent = speedup.toFixed(2) + "x";
  document.getElementById("statEficiencia").textContent = eficiencia.toFixed(1) + "%";

  generarGanttPipeline(k, n);
}

function generarGanttPipeline(k, n) {
  const etapasBase = ["IF", "ID", "EX", "MEM", "WB"];
  const etapas = [];

  for (let i = 0; i < k; i++) {
    etapas.push(etapasBase[i] || "E" + (i + 1));
  }

  const ciclosTotales = k + (n - 1);
  let html = "<table>";
  html += "<thead><tr><th>Instr.</th>";

  for (let c = 1; c <= ciclosTotales; c++) {
    html += `<th>C${c}</th>`;
  }

  html += "</tr></thead><tbody>";

  for (let i = 1; i <= n; i++) {
    html += `<tr><td>I${i}</td>`;

    for (let c = 1; c <= ciclosTotales; c++) {
      const etapaIndex = c - i;

      if (etapaIndex >= 0 && etapaIndex < k) {
        html += `<td><span class="stage">${etapas[etapaIndex]}</span></td>`;
      } else {
        html += `<td class="empty-stage">-</td>`;
      }
    }

    html += "</tr>";
  }

  html += "</tbody></table>";
  document.getElementById("ganttPipeline").innerHTML = html;
}

document.addEventListener("DOMContentLoaded", () => {
  if (document.getElementById("k")) {
    calcularPipeline();
  }
});
function calcularMonociclo() {
  const im = Number(document.getElementById("im").value);
  const rfRead = Number(document.getElementById("rfRead").value);
  const alu = Number(document.getElementById("alu").value);
  const dm = Number(document.getElementById("dm").value);
  const rfWrite = Number(document.getElementById("rfWrite").value);

  if (im <= 0 || rfRead <= 0 || alu <= 0 || dm <= 0 || rfWrite <= 0) {
    alert("Ingrese valores mayores que cero.");
    return;
  }

  const tipoR = im + rfRead + alu + rfWrite;
  const lw = im + rfRead + alu + dm + rfWrite;
  const sw = im + rfRead + alu + dm;
  const beq = im + rfRead + alu;

  const periodo = Math.max(tipoR, lw, sw, beq);
  const frecuenciaMHz = 1000000 / periodo;
  const slack = periodo - beq;
  const eficiencia = (beq / periodo) * 100;

  document.getElementById("tipoR").textContent = tipoR + " ps";
  document.getElementById("lw").textContent = lw + " ps";
  document.getElementById("sw").textContent = sw + " ps";
  document.getElementById("beq").textContent = beq + " ps";
  document.getElementById("cardTipoR").textContent = tipoR + " ps";
document.getElementById("cardLw").textContent = lw + " ps";
document.getElementById("cardSw").textContent = sw + " ps";
document.getElementById("cardBeq").textContent = beq + " ps";

  document.getElementById("statPeriodo").textContent = periodo + " ps";
  document.getElementById("statFrecuencia").textContent = frecuenciaMHz.toFixed(2) + " MHz";
  document.getElementById("statSlack").textContent = slack + " ps";
  document.getElementById("statEficienciaMono").textContent = eficiencia.toFixed(1) + "%";

}

document.addEventListener("DOMContentLoaded", () => {
  if (document.getElementById("im")) {
    calcularMonociclo();
  }
});
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

function cargarModuloRisc() {
  if (document.body.dataset.page !== "risc") return;

  pintarRegistrosRisc();
  pintarMemoriaRisc();
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

  lineas.forEach(linea => linea.classList.remove("active-line"));

  if (lineas[indice]) {
    lineas[indice].classList.add("active-line");
  }
}

function ejecutarRisc() {
  if (document.body.dataset.page !== "risc") return;

  reiniciarRisc();

  let paso = 0;

  const ejecucion = [
    () => {
      registrosRisc.R0 = "0x100";
      agregarHistorialRisc(++paso, instruccionesRisc[0], "Carga inmediata", "R0 = 0x100");
    },
    () => {
      registrosRisc.R1 = memoriaRisc["0x100"].valor;
      agregarHistorialRisc(++paso, instruccionesRisc[1], "Load", "R1 = 12");
    },
    () => {
      registrosRisc.R2 = memoriaRisc["0x104"].valor;
      agregarHistorialRisc(++paso, instruccionesRisc[2], "Load", "R2 = 8");
    },
    () => {
      registrosRisc.R3 = memoriaRisc["0x108"].valor;
      agregarHistorialRisc(++paso, instruccionesRisc[3], "Load", "R3 = 15");
    },
    () => {
      registrosRisc.R4 = memoriaRisc["0x10C"].valor;
      agregarHistorialRisc(++paso, instruccionesRisc[4], "Load", "R4 = 10");
    },
    () => {
      registrosRisc.R5 = registrosRisc.R1 + registrosRisc.R2;
      actualizarALU("ADD", registrosRisc.R1, registrosRisc.R2, registrosRisc.R5);
      agregarHistorialRisc(++paso, instruccionesRisc[5], "ALU", "R5 = 20");
    },
    () => {
      registrosRisc.R6 = registrosRisc.R3 - registrosRisc.R4;
      actualizarALU("SUB", registrosRisc.R3, registrosRisc.R4, registrosRisc.R6);
      agregarHistorialRisc(++paso, instruccionesRisc[6], "ALU", "R6 = 5");
    },
    () => {
      registrosRisc.R7 = registrosRisc.R5 * registrosRisc.R6;
      actualizarALU("MUL", registrosRisc.R5, registrosRisc.R6, registrosRisc.R7);
      agregarHistorialRisc(++paso, instruccionesRisc[7], "ALU", "R7 = 100");
    },
    () => {
      memoriaRisc["0x110"].valor = registrosRisc.R7;
      document.getElementById("resultadoRisc").textContent = registrosRisc.R7;
      agregarHistorialRisc(++paso, instruccionesRisc[8], "Store", "Memoria[0x110] = 100");
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

function reiniciarRisc() {
  Object.keys(registrosRisc).forEach(reg => registrosRisc[reg] = 0);

  memoriaRisc["0x100"].valor = 12;
  memoriaRisc["0x104"].valor = 8;
  memoriaRisc["0x108"].valor = 15;
  memoriaRisc["0x10C"].valor = 10;
  memoriaRisc["0x110"].valor = "Pendiente";

  document.getElementById("historialRisc").innerHTML = "";
  document.getElementById("resultadoRisc").textContent = "Pendiente";

  actualizarALU("---", "---", "---", "---");

  pintarRegistrosRisc();
  pintarMemoriaRisc();
}

document.addEventListener("DOMContentLoaded", cargarModuloRisc);