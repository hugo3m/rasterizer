import { Dispatch, SetStateAction } from "react";
import { Nullable } from "./type";

import { Rasterizer, MainModule } from "../lib/cpp";

enum Event {
    Up = 1,
    Down = 0,
}

type InputInfo = {
    forward: boolean
    backward: boolean
    up: boolean
    down: boolean
    left: boolean
    right: boolean
};

class Engine {
    static _instance?: Engine;

    cpp: MainModule;
    canvas: HTMLCanvasElement;
    height: number;
    deltaTime: number;
    inputInfo: InputInfo;
    rasterizer: Rasterizer;
    refreshRate: number;
    setFps: Dispatch<SetStateAction<number>>;
    setInputInfo: Dispatch<SetStateAction<Nullable<InputInfo>>>;
    width: number;
    isDestroyed: boolean;

    private constructor(rasterizer: Rasterizer, cpp: MainModule, canvas: HTMLCanvasElement, width: number, height: number, setFps: Dispatch<SetStateAction<number>>, setInputInfo: Dispatch<SetStateAction<Nullable<InputInfo>>>) {
        this.rasterizer = rasterizer;
        this.canvas = canvas;
        this.cpp = cpp;
        this.width = width;
        this.height = height;
        this.inputInfo = {forward: false, backward: false, left:false, right:false, up:false, down: false};
        this.refreshRate = 60;
        this.isDestroyed = false;
        this.deltaTime = 0;
        this.setFps = setFps;
        this.setInputInfo = setInputInfo;
        this.update();

        addEventListener("keydown", (event) => {
            this.handleEvent(event.key, Event.Down);
        });

        addEventListener("keyup", (event) => {
            this.handleEvent(event.key, Event.Up);
        });
    }

    public static create(rasterizer: Rasterizer, cpp: MainModule, canvas: HTMLCanvasElement, width: number, height: number, setFps: Dispatch<SetStateAction<number>>, setInputInfo: Dispatch<SetStateAction<Nullable<InputInfo>>>) {
        if (!Engine._instance) {
            Engine._instance = new Engine(rasterizer, cpp, canvas, width, height, setFps, setInputInfo);
        }
    }

    public static destroy(){
        if(Engine._instance){
            Engine._instance.isDestroyed = true;
            Engine._instance.rasterizer.delete();
            delete Engine._instance;
        }
    }

    private update() {
        if(this.isDestroyed) return;
        const ctx = this.canvas.getContext("2d")
        if (!ctx) return;
        this.setFps(1 / this.deltaTime);
        this.setInputInfo(this.inputInfo);
        const startTime: number = Date.now();
        this.rasterizer.Input(this.inputInfo.forward,
            this.inputInfo.backward,
            this.inputInfo.left,
            this.inputInfo.right,
            this.inputInfo.up,
            this.inputInfo.down,
            this.deltaTime);
        this.rasterizer.Render(this.deltaTime);
        const ptr: number = this.rasterizer.DrawNative();
        const image = new Uint8ClampedArray(this.cpp.HEAPU8.buffer, ptr, this.width * this.height * 4);
        ctx.putImageData(new ImageData(image, this.width, this.height), 0, 0);
        this.cpp.freeBuffer(ptr);
        const endTime: number = Date.now();
        const elapsedTimeMs: number = endTime - startTime;
        const minTimeMs = (1 / this.refreshRate) * 1000;
        const timeToWait = minTimeMs > elapsedTimeMs ? minTimeMs - elapsedTimeMs : 0;
        this.deltaTime = (elapsedTimeMs + timeToWait) / 1000;
        setTimeout(this.update.bind(this), timeToWait);
    };

    private mapEventToBoolean(event: Event): boolean {
        switch(event){
            case Event.Down:
                return true;
            case Event.Up:
                return false;
            default:
                return false;
        }
    }

    private handleEvent(key: string, event: Event){
        const eventBoolean = this.mapEventToBoolean(event);
        switch(key){
            case "w":
                this.inputInfo.forward = eventBoolean;
                break
            case "s":
                this.inputInfo.backward = eventBoolean;
                break;
            case "a":
                this.inputInfo.left = eventBoolean;
                break;
            case "d":
                this.inputInfo.right = eventBoolean;
                break;
            case "q":
                this.inputInfo.up = eventBoolean;
                break;
            case "e":
                this.inputInfo.down = eventBoolean;
                break;
            case "ArrowUp":
                this.inputInfo.forward = eventBoolean;
                break
            case "ArrowDown":
                this.inputInfo.backward = eventBoolean;
                break;
            case "ArrowLeft":
                this.inputInfo.left = eventBoolean;
                break;
            case "ArrowRight":
                this.inputInfo.right = eventBoolean;
                break;
            default:
                break;
        }
    }

}

export default Engine;

export { type InputInfo };