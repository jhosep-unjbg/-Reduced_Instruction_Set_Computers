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