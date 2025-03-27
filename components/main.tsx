"use client";

import Engine, {InputInfo} from "../utils/engine";
import { useEffect, useRef, useState } from 'react';

import { MainModule, DrawingMethod } from "../lib/cpp.js";

import { Nullable } from '@/utils/type';
import { useCpp } from "@/utils/hooks/useCpp";
import Slider from '@mui/material/Slider';
import Input from "./input";

export default function Test() {

  // render
  const canvasRef = useRef<HTMLCanvasElement>(null);
  // state
  const [pixels, setPixels] = useState<number>(600);
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
      const rasterizer = new cpp.Rasterizer(pixels, pixels);
      Engine.create(rasterizer, canvasRef.current, pixels, pixels, setFps, setInputInfo);
    };
    run();
    return () => {
        Engine.destroy();
    }
  }, [cpp, pixels]);



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
        <div >
        {!cpp ? <div className="flex flex-2 flex-col max-w-[30vw] min-w-[30vw]">
            <p>Loading...</p>
          </div>
            :
          <div className="flex flex-2 flex-col max-w-[30vw] min-w-[30vw]">
            <p>FPS: {fps.toFixed(0)}</p>
            <canvas ref={canvasRef} width={pixels} height={pixels}/>
            {inputInfo ? <div className="flex flex-col items-center">
              <div className="flex flex-row">
                  <Input input="Q" isDown={inputInfo.up}/>
                  <Input input="W" isDown={inputInfo.forward}/>
                  <Input input="E" isDown={inputInfo.down}/>
              </div>
              <div className="flex flex-row">
                  <Input input="A" isDown={inputInfo.left}/>
                  <Input input="S" isDown={inputInfo.backward}/>
                  <Input input="D" isDown={inputInfo.right}/>
              </div>
              </div> : null}
            </div>
        }
        </div>
        <div className="flex flex-1 flex-col p-12">
          <span>Number of pixels width and height</span>
          <Slider
              value={pixels}
              onChange={(event, value) => setPixels(value as number)}
              marks
              valueLabelDisplay="auto"
              min={100}
              step={100}
              max={1000}
          />
        </div>
        </div>
      </div>
    );
}
