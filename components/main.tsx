"use client";

import { useEffect, useRef } from 'react';

export default function Test() {

  const canvasRef = useRef<HTMLCanvasElement>(null);

  useEffect(() => {

      const run = async () => {
        if (!canvasRef.current) return;
        const ctx = canvasRef.current.getContext("2d");
        if (!ctx) return ;
        const CPP = await (await import('../lib/cpp.js')).default();
        const draw = CPP.draw();
        const array: number[] = [];
        console.log(draw.size());
        for (let i = 0; i < draw.size(); i++){
          array.push(draw.get(i) as number);
        }
        console.log(array);
        ctx.putImageData(new ImageData(new Uint8ClampedArray(array), 200, 200), 0, 0);
      };
      run();
  }, []);

  return (
    <div className="flex flex-1 flex-col">
      <div className="flex flex-row justify-center">
        <div className="flex flex-1 flex-col p-12">
            <span>Presentation:</span>
            <p>
                Homemade rasterizer made by <a className="text-blue-700" href="https://github.com/hugo3m">hugo3m</a> inspired from
                <a className="text-blue-700" href="https://gabrielgambetta.com/computer-graphics-from-scratch/index.html"> Computer graphics from scratch, Gabriel Gambetta</a>.
                  Built using C++ web assembly and NextJS. You can find the repository at <a className="text-blue-700" href="https://github.com/hugo3m/rasterizer/">hugo3m/rasterizer</a>.
            </p>
        </div>
        <div className="flex flex-2 flex-col max-w-[30vw] min-w-[30vw]">
          <canvas ref={canvasRef} width={600} height={600}/>
        </div>
        </div>
      </div>
    );
}
