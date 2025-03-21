"use client";

import Engine, {InputInfo} from "../utils/engine";
import { useEffect, useRef, useState } from 'react';

import { MainModule, DrawingMethod } from "../lib/cpp.js";

import { Nullable } from '@/utils/type';
import { useCpp } from "@/utils/hooks/useCpp";

export default function Test() {

  // render
  const canvasRef = useRef<HTMLCanvasElement>(null);
  // state
  const [drawingMethod, setDrawingMethod] = useState<DrawingMethod | null>(null); 
  const [inputInfo, setInputInfo] = useState<Nullable<InputInfo>>(null);
  const [fps, setFps] = useState<number>(0);

  const cpp: MainModule | undefined = useCpp();

  useEffect(() => {
    const run = async () => {
      if(!cpp) return;
      if (!canvasRef.current) return;
      const ctx = canvasRef.current.getContext("2d");
      if (!ctx) return ;
      const rasterizer = new cpp.Rasterizer();
      Engine.create(rasterizer, canvasRef.current, 200, 200, setFps, setInputInfo);
    };
    run();
    return () => {
        Engine.destroy();
    }
  }, [cpp]);



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
        {!cpp ? <div>
            <p>Loading...</p>
          </div>
            : 
          <>
          <p>FPS: {fps.toFixed(0)}</p>
          <canvas ref={canvasRef} width={600} height={600}/>
          </>
        }
        </div>
        {/* <div className="flex flex-1 flex-col p-12">
          {drawingMethodValues.length > 0 ? <Select options={drawingMethodValues.map((value) => ({option: value, label: value.value}))}/> : null}
        </div> */}
        </div>
      </div>
    );
}
