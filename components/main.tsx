"use client";

import Engine, {InputInfo} from "../utils/engine";
import { useEffect, useRef, useState } from 'react';

import { MainModule, ShadingMethod } from "../lib/cpp.js";
import FormControl from '@mui/material/FormControl';
import InputLabel from '@mui/material/InputLabel';
import Box from '@mui/material/Box';
import Select, { SelectChangeEvent } from '@mui/material/Select';
import MenuItem from '@mui/material/MenuItem';

import { Nullable, SelectAttr } from '@/utils/type';
import { useCpp } from "@/utils/hooks/useCpp";
import Slider from '@mui/material/Slider';
import Input from "./input";

export default function Test() {

  // render
  const canvasRef = useRef<HTMLCanvasElement>(null);
  // state
  const [pixels, setPixels] = useState<number>(600);
  const [shadingMethods, setShadingMethods] = useState<SelectAttr<ShadingMethod>[]>([]);
  const [shadingMethod, setShadingMethod] = useState<Nullable<SelectAttr<ShadingMethod>>>(null); 
  const [inputInfo, setInputInfo] = useState<Nullable<InputInfo>>(null);
  const [fps, setFps] = useState<number>(0);


  const cpp: MainModule | undefined = useCpp();

  const createShadingMethod = (dMeth: ShadingMethod): SelectAttr<ShadingMethod> => {
    if(!cpp) throw Error('createShadingMethod: cpp undefined');
    switch(dMeth){
      case cpp.ShadingMethod.FLAT_SHADING:
        return { value: dMeth, label: "Flat shading"};
      case cpp.ShadingMethod.GOUREAU_SHADING:
        return { value: dMeth, label: "Goureau shading"};
      case cpp.ShadingMethod.PONG_SHADING:
        return { value: dMeth, label: "Pong shading"};
      case cpp.ShadingMethod.WIREFRAMED:
        return { value: dMeth, label: "Wireframed"}; 
      default:
        return { value: dMeth, label: "Pong shading"};
    }
  };

  useEffect(() => {
    const init = async () => {
      if(!cpp) return;
      setShadingMethods([createShadingMethod(cpp.ShadingMethod.FLAT_SHADING),
        createShadingMethod(cpp.ShadingMethod.GOUREAU_SHADING),
        createShadingMethod(cpp.ShadingMethod.PONG_SHADING),
        createShadingMethod(cpp.ShadingMethod.WIREFRAMED),
       ]);
      setShadingMethod(createShadingMethod(cpp.ShadingMethod.PONG_SHADING));
    };
    init();
  }, [cpp]);

  useEffect(() => {
    const run = async () => {
      if(!cpp) return;
      if (!canvasRef.current) return;
      const ctx = canvasRef.current.getContext("2d");
      if (!ctx) return;
      if (!shadingMethod) return;
      const rasterizer = new cpp.Rasterizer(pixels, pixels, shadingMethod.value);
      Engine.create(rasterizer, cpp, canvasRef.current, pixels, pixels, setFps, setInputInfo);
    };
    run();
    return () => {
      Engine.destroy();
    }
  }, [cpp, pixels, shadingMethod]);

  return (
    <div className="flex flex-1 flex-col">
      <div className="flex justify-center flex-col sm:flex-row">
        <div className="flex flex-1 flex-col p-12">
            <span>Presentation:</span>
            <p>
                Homemade rasterizer made by <a className="text-blue-700" href="https://github.com/hugo3m">hugo3m</a> inspired from
                <a className="text-blue-700" href="https://gabrielgambetta.com/computer-graphics-from-scratch/index.html"> Computer graphics from scratch, Gabriel Gambetta</a>.
                  Built using C++ web assembly and NextJS. You can find the repository at <a className="text-blue-700" href="https://github.com/hugo3m/rasterizer/">hugo3m/rasterizer</a>
                  , or look at the <a className="text-blue-700" href="https://raytracer-hugo3ms-projects.vercel.app/">raytracer</a>.
            </p>
        </div>
        <div >
        {!cpp ? <div className="flex flex-2 flex-col items-center">
            <p>Loading...</p>
          </div>
            :
          <div className="flex flex-2 flex-col items-center">
            <p>FPS: {fps.toFixed(0)}</p>
            <canvas className="max-w-[70vw] min-w-[70vw] sm:max-w-[35vw] sm:min-w-[35vw]" ref={canvasRef} width={pixels} height={pixels}/>
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
          <div>
            <span>Number of pixels width and height</span>
            <Slider
                value={pixels}
                onChange={(event, value) => setPixels(value as number)}
                marks
                valueLabelDisplay="auto"
                min={400}
                step={200}
                max={1200}
            />
          </div>
          <div>
          {shadingMethods.length > 0 && shadingMethod !== null ? <Box sx={{ minWidth: 120 }}>
            <FormControl fullWidth>
              <InputLabel id="demo-simple-select-label" sx={{ color: '#1876d1' }}>Shading method</InputLabel>
                <Select
                  labelId="demo-simple-select-label"
                  id="demo-simple-select"
                  value={shadingMethod.value}
                  label="Shading method"
                  onChange={(event) => {setShadingMethod(createShadingMethod(event.target.value as ShadingMethod));}}
                  sx={{
                    color: '#1876d1',
                    '.MuiOutlinedInput-notchedOutline': {
                      borderColor: '#1876d1',
                    },
                    '&.Mui-focused .MuiOutlinedInput-notchedOutline': {
                      borderColor: '#1876d1',
                    },
                    '&:hover .MuiOutlinedInput-notchedOutline': {
                      borderColor: '#1876d1',
                    },
                    '.MuiSvgIcon-root': {
                      color: '#1876d1',
                    },
                  }}
                >
                  {shadingMethods.map((d, index) => <MenuItem key={index} value={d.value}>{d.label}</MenuItem>)}
                </Select>
            </FormControl>
          </Box>: null}
          </div>
        </div>
        </div>
      </div>
    );
}
