const img = document.getElementById('frame') as HTMLImageElement;
const res = document.getElementById('res')!;
const fps = document.getElementById('fps')!;

// A tiny base64 grayscale PNG (1x1) just as a placeholder. Replace with your saved processed frame.
img.src = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVR4nGNgYAAAAAMAAWgmWQ0AAAAASUVORK5CYII=';
res.textContent = '640x480';

let f = 0;
setInterval(() => { f = (f + 13) % 60; fps.textContent = String(10 + (f % 20)); }, 1000);
