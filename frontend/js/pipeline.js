async function inicializarPipeline() {
  await calcularPipeline();

  document
    .getElementById("btnCalcularPipeline")
    ?.addEventListener("click", calcularPipeline);
}

async function calcularPipeline() {
  const k = Number(document.getElementById("k").value);
  const n = Number(document.getElementById("n").value);
  const tau = Number(document.getElementById("tau").value);

  if (k <= 0 || n <= 0 || tau <= 0) {
    alert("Ingrese valores mayores que cero.");
    return;
  }

  const resultado = await postData("/api/pipeline", {
    k,
    n,
    tau
  });
 

  if (!resultado) {
    alert("No se pudo conectar con el backend Crow.");
    return;
  }

  const ciclos = resultado.ciclos;
  const tiempo = resultado.tiempoTotal;
  const speedup = resultado.speedup;
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