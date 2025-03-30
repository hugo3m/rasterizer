import { DrawingMethod } from "@/lib/cpp";

type Nullable<T> = T | null;

export {
    type Nullable
};


export type SelectAttr<T> = {
    value: T,
    label: string
}