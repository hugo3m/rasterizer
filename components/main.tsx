"use client";

import Image from "next/image";
import { useEffect } from 'react';

export default function Test() {

  useEffect(() => {
    if (typeof window !== 'undefined') {
      const loadWasm = async () => {
        const CPP = await (await import('../lib/cpp.js')).default();
        CPP.myFunction();
      };
      loadWasm();
    }
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
          <canvas width={600} height={600}/>
        </div>
        </div>
      </div>
    );
}
