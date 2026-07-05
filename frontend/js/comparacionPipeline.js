function inicializarComparacionPipeline() {
  compararPipelineMonociclo();

  document
    .getElementById("btnCompararPipeline")
    ?.addEventListener("click", compararPipelineMonociclo);
}

function compararPipelineMonociclo() {
  const k = Number(document.getElementById("cmpK").value);
  const n = Number(document.getElementById("cmpN").value);
  const tau = Number(document.getElementById("cmpTau").value);

  if (k <= 0 || n <= 0 || tau <= 0) {
    alert("Ingrese valores mayores que cero.");
    return;
  }

  const ciclosPipeline = k + (n - 1);
  const ciclosMonociclo = n * k;

  const tiempoPipeline = ciclosPipeline * tau;
  const tiempoMonociclo = ciclosMonociclo * tau;

  const speedup = tiempoMonociclo / tiempoPipeline;
  const eficiencia = (speedup / k) * 100;

  document.getElementById("cmpPipeCiclos").textContent = ciclosPipeline;
  document.getElementById("cmpMonoCiclos").textContent = ciclosMonociclo;
  document.getElementById("cmpSpeedup").textContent = speedup.toFixed(2) + "x";
  document.getElementById("cmpEficiencia").textContent = eficiencia.toFixed(1) + "%";

  document.getElementById("tablaPipeCiclos").textContent = ciclosPipeline + " ciclos";
  document.getElementById("tablaMonoCiclos").textContent = ciclosMonociclo + " ciclos";

  document.getElementById("tablaPipeTiempo").textContent = tiempoPipeline.toFixed(2) + " ns";
  document.getElementById("tablaMonoTiempo").textContent = tiempoMonociclo.toFixed(2) + " ns";

  document.getElementById("conclusionPipelineMono").textContent =
    "Pipeline reduce el tiempo total frente al modelo no segmentado.";

  document.getElementById("resultadoPipelineMono").textContent =
    `Para ${n} instrucciones, Pipeline logra un speedup de ${speedup.toFixed(2)}x.`;

  dibujarGraficoPipelineMonociclo(k, n, tau);
}

function dibujarGraficoPipelineMonociclo(k, n, tau) {
  const canvas = document.getElementById("graficoPipelineMonociclo");
  if (!canvas) return;

  const ctx = canvas.getContext("2d");
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  const padding = 60;
  const puntos = [];

  for (let i = 1; i <= n; i++) {
    puntos.push({
      instrucciones: i,
      pipeline: (k + (i - 1)) * tau,
      monociclo: (i * k) * tau
    });
  }

  const maxX = n;
  const maxY = Math.max(...puntos.map(p => p.monociclo));

  function x(valor) {
    return padding + (valor / maxX) * (canvas.width - padding * 2);
  }

  function y(valor) {
    return canvas.height - padding - (valor / maxY) * (canvas.height - padding * 2);
  }

  ctx.strokeStyle = "#334155";
  ctx.lineWidth = 2;

  ctx.beginPath();
  ctx.moveTo(padding, padding);
  ctx.lineTo(padding, canvas.height - padding);
  ctx.lineTo(canvas.width - padding, canvas.height - padding);
  ctx.stroke();

  ctx.fillStyle = "#94a3b8";
  ctx.font = "13px Segoe UI";
  ctx.fillText("Tiempo (ns)", 15, 30);
  ctx.fillText("Instrucciones", canvas.width - 150, canvas.height - 20);

  function dibujarLinea(clave, color, etiqueta) {
    ctx.beginPath();

    puntos.forEach((p, index) => {
      const px = x(p.instrucciones);
      const py = y(p[clave]);

      if (index === 0) ctx.moveTo(px, py);
      else ctx.lineTo(px, py);
    });

    ctx.strokeStyle = color;
    ctx.lineWidth = 3;
    ctx.stroke();

    const ultimo = puntos[puntos.length - 1];
    ctx.fillStyle = color;
    ctx.font = "14px Segoe UI";
    ctx.fillText(etiqueta, x(ultimo.instrucciones) - 90, y(ultimo[clave]) - 10);
  }

  dibujarLinea("pipeline", "#38bdf8", "Pipeline");
  dibujarLinea("monociclo", "#22c55e", "Monociclo");
}