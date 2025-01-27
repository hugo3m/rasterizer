import { Dispatch, SetStateAction } from "react";
import { Nullable } from "./type";

import { Rasterizer } from "../lib/cpp";

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

    canvas: HTMLCanvasElement;
    height: number;
    deltaTime: number;
    inputInfo: InputInfo;
    rasterizer: Rasterizer;
    refreshRate: number;
    setFps: Dispatch<SetStateAction<number>>
    setInputInfo: Dispatch<SetStateAction<Nullable<InputInfo>>>
    width: number;
    isDestroyed: boolean;

    private constructor(rasterizer: Rasterizer, canvas: HTMLCanvasElement, width: number, height: number, setFps: Dispatch<SetStateAction<number>>, setInputInfo: Dispatch<SetStateAction<Nullable<InputInfo>>>) {
        this.rasterizer = rasterizer;
        this.canvas = canvas;
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

    public static create(rasterizer: Rasterizer, canvas: HTMLCanvasElement, width: number, height: number, setFps: Dispatch<SetStateAction<number>>, setInputInfo: Dispatch<SetStateAction<Nullable<InputInfo>>>) {
        if (!Engine._instance) {
            Engine._instance = new Engine(rasterizer, canvas, width, height, setFps, setInputInfo);
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
        console.log(this.inputInfo);
        this.rasterizer.Input(this.inputInfo.forward,
            this.inputInfo.backward,
            this.inputInfo.left,
            this.inputInfo.right,
            this.inputInfo.up,
            this.inputInfo.down,
            this.deltaTime);
        this.rasterizer.Render();
        const draw = this.rasterizer.Draw();
        const array: number[] = [];
        for (let i = 0; i < draw.size(); i++){
            array.push(draw.get(i) as number);
        }
        ctx.putImageData(new ImageData(new Uint8ClampedArray(array), this.width, this.height), 0, 0);
        const elapsedTimeMs: number = Date.now() - startTime;
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